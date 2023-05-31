#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include <string.h>
#include "pulse3.pio.h"
#include "pio_spi_16_bit.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define GPIO_PIN 2
#define READY_SIGNAL "READY"
#define SIGNAL_SIZE 5

void dac_write(const pio_spi_inst_t *spi, uint16_t value) {
    uint16_t cmd = 0x7000 | (value & 0x0FFF);
    gpio_put(spi->cs_pin, 0);
    pio_spi_write16_blocking(spi, &cmd, 1);
    gpio_put(spi->cs_pin, 1);
}

int main() {
    stdio_init_all();
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    gpio_init(GPIO_PIN);
    gpio_set_dir(GPIO_PIN, GPIO_OUT);

    uart_puts(UART_ID, "Pico is ready and listening...\n");

    char received[SIGNAL_SIZE + 1] = {0};

    PIO pio = pio0;
    uint offset = pio_add_program(pio, &pulse_program);

    uint sm1 = pio_claim_unused_sm(pio, true);

    bool ready_signal_received = false;

    while (!ready_signal_received) {
        uart_puts(UART_ID, "Waiting for data...\n");

        if (uart_is_readable(UART_ID)) {
            for (int i = 0; i < SIGNAL_SIZE - 1; i++) {
                received[i] = received[i + 1];
            }

            received[SIGNAL_SIZE - 1] = uart_getc(UART_ID);

            uart_puts(UART_ID, "Received signal: ");
            uart_puts(UART_ID, received);
            uart_puts(UART_ID, "\n");

            if (strcmp(received, READY_SIGNAL) == 0) {
                pulse_program_init(pio, sm1, offset, 2);
                uart_puts(UART_ID, "Received READY signal, toggling GPIO pin...\n");
                ready_signal_received = true;
            }
        }
    }

    // If received READY_SIGNAL, proceed with SPI tasks
    if(ready_signal_received){
        pio_spi_inst_t spi = {
                .pio = pio0,
                .sm = 0,
                .cs_pin = PICO_DEFAULT_SPI_CSN_PIN
        };

        gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
        gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
        gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);

        uint offset_spi = pio_add_program(spi.pio, &spi_cpha0_program);

        pio_spi_init(spi.pio, spi.sm, offset_spi,
                 16,
                 2,
                 false,
                 false,
                 PICO_DEFAULT_SPI_SCK_PIN,
                 PICO_DEFAULT_SPI_TX_PIN,
                 PICO_DEFAULT_SPI_RX_PIN
        );

        // Output a ramp
        uint16_t value = 0;
        while (1) {
            if (value >= 1000) {
                value = 0;
            }
            dac_write(&spi, value);
            value+=50;
            sleep_us(4);
        }
    }
    return 0;
}

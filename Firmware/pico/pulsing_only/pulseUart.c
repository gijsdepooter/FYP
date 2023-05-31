#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include <string.h>
#include "pulse3.pio.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define GPIO_PIN 2  // Change this to your desired GPIO pin

#define READY_SIGNAL "READY"
#define SIGNAL_SIZE 5  // Number of characters in READY_SIGNAL

int main() {
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    gpio_init(GPIO_PIN);
    gpio_set_dir(GPIO_PIN, GPIO_OUT);

    uart_puts(UART_ID, "Pico is ready and listening...\n");

    char received[SIGNAL_SIZE + 1] = {0};

    // Add the PIO program
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &pulse_program);
    printf("Loaded program at %d\n", offset);

    uint sm1 = pio_claim_unused_sm(pio, true);

    bool ready_signal_received = false;

    while (!ready_signal_received) {
        uart_puts(UART_ID, "Waiting for data...\n");

        // Check if data is available to read
        if (uart_is_readable(UART_ID)) {
            // Shift the received characters to the left
            for (int i = 0; i < SIGNAL_SIZE - 1; i++) {
                received[i] = received[i + 1];
            }

            // Read a character
            received[SIGNAL_SIZE - 1] = uart_getc(UART_ID);

            // Print the received signal
            uart_puts(UART_ID, "Received signal: ");
            uart_puts(UART_ID, received);
            uart_puts(UART_ID, "\n");

            // Check if we received the ready signal
            if (strcmp(received, READY_SIGNAL) == 0) {
                pulse_program_init(pio, sm1, offset, 2);
                uart_puts(UART_ID, "Received READY signal, toggling GPIO pin...\n");
                ready_signal_received = true;
            }
        }
    }
}

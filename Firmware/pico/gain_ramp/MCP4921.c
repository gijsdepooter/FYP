/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pio_spi_16_bit.h"

// This example uses PIO to erase, program and read back a SPI serial flash
// memory.

// ----------------------------------------------------------------------------
// Generic serial flash code

void dac_write(const pio_spi_inst_t *spi, uint16_t value) {
    uint16_t cmd = 0x7000 | (value & 0x0FFF);  // Control bits: 0111 (write, unbuffered, 1x, active)
    gpio_put(spi->cs_pin, 0);
    pio_spi_write16_blocking(spi, &cmd, 1);
    gpio_put(spi->cs_pin, 1);
}


// ----------------------------------------------------------------------------
// Example prograM

int main() {
    stdio_init_all();
#if !defined(PICO_DEFAULT_SPI_SCK_PIN) || !defined(PICO_DEFAULT_SPI_TX_PIN) || !defined(PICO_DEFAULT_SPI_RX_PIN) || !defined(PICO_DEFAULT_SPI_CSN_PIN)
#warning pio/spi/spi_flash example requires a board with SPI pins
    puts("Default SPI pins were not defined");
#else

    puts("PIO SPI Example");

    pio_spi_inst_t spi = {
            .pio = pio0,
            .sm = 0,
            .cs_pin = PICO_DEFAULT_SPI_CSN_PIN
    };

    gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
    gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);

    uint offset = pio_add_program(spi.pio, &spi_cpha0_program);
    printf("Loaded program at %d\n", offset);

    pio_spi_init(spi.pio, spi.sm, offset,
             16,       // 16 bits per SPI frame
             2,  // 1 MHz @ 125 clk_sys
             false,   // CPHA = 0
             false,   // CPOL = 0
             PICO_DEFAULT_SPI_SCK_PIN,
             PICO_DEFAULT_SPI_TX_PIN,
             PICO_DEFAULT_SPI_RX_PIN
    );

    // Make the 'SPI' pins available to picotool
    bi_decl(bi_4pins_with_names(PICO_DEFAULT_SPI_RX_PIN, "SPI RX", PICO_DEFAULT_SPI_TX_PIN, "SPI TX", PICO_DEFAULT_SPI_SCK_PIN, "SPI SCK", PICO_DEFAULT_SPI_CSN_PIN, "SPI CS"));

    // Test: Output a ramp
    uint16_t value = 0;
    while (1) {
        if (value >= 1000) {
            value = 0;  // Reset DAC value to zero if it's reached 1000
        }
        dac_write(&spi, value);
        value+=50;
        sleep_us(4);  // Slow down the ramp for testing
    }
    return 0;
#endif
}

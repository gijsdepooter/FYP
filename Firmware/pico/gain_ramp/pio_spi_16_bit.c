#include "pio_spi_16_bit.h"

void __time_critical_func(pio_spi_write16_blocking)(const pio_spi_inst_t *spi, const uint16_t *src, size_t len) {
    size_t tx_remain = len, rx_remain = len;
    io_rw_16 *txfifo = (io_rw_16 *) &spi->pio->txf[spi->sm];
    io_rw_16 *rxfifo = (io_rw_16 *) &spi->pio->rxf[spi->sm];
    while (tx_remain || rx_remain) {
        if (tx_remain && !pio_sm_is_tx_fifo_full(spi->pio, spi->sm)) {
            *txfifo = *src++;
            --tx_remain;
        }
        if (rx_remain && !pio_sm_is_rx_fifo_empty(spi->pio, spi->sm)) {
            (void) *rxfifo;
            --rx_remain;
        }
    }
}

void __time_critical_func(pio_spi_read16_blocking)(const pio_spi_inst_t *spi, uint16_t *dst, size_t len) {
    size_t tx_remain = len, rx_remain = len;
    io_rw_16 *txfifo = (io_rw_16 *) &spi->pio->txf[spi->sm];
    io_rw_16 *rxfifo = (io_rw_16 *) &spi->pio->rxf[spi->sm];
    while (tx_remain || rx_remain) {
        if (tx_remain && !pio_sm_is_tx_fifo_full(spi->pio, spi->sm)) {
            *txfifo = 0;
            --tx_remain;
        }
        if (rx_remain && !pio_sm_is_rx_fifo_empty(spi->pio, spi->sm)) {
            *dst++ = *rxfifo;
            --rx_remain;
        }
    }
}

void __time_critical_func(pio_spi_write16_read16_blocking)(const pio_spi_inst_t *spi, uint16_t *src, uint16_t *dst,
                                                           size_t len) {
    size_t tx_remain = len, rx_remain = len;
    io_rw_16 *txfifo = (io_rw_16 *) &spi->pio->txf[spi->sm];
    io_rw_16 *rxfifo = (io_rw_16 *) &spi->pio->rxf[spi->sm];
    while (tx_remain || rx_remain) {
        if (tx_remain && !pio_sm_is_tx_fifo_full(spi->pio, spi->sm)) {
            *txfifo = *src++;
            --tx_remain;
        }
        if (rx_remain && !pio_sm_is_rx_fifo_empty(spi->pio, spi->sm)) {
            *dst++ = *rxfifo;
            --rx_remain;
        }
    }
}

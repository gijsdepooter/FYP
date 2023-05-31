#include <stdint.h>             // uint8_t, uint16_t
#include <fcntl.h>              // open
#include <linux/spi/spidev.h>   // SPI bus definitions
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
void output_dac_value(int fd, uint16_t val) {
    uint8_t writeBuf[2];

    // control bits and high data (MSB)
    writeBuf[0] = (0x3 << 4) | (val >> 8);
    // low data (LSB)
    writeBuf[1] = val;

    // write the two bytes to the DAC
    if (write(fd, writeBuf, 2) != 2) {
        printf("Write to register failed.");
        exit(1);
    }
}

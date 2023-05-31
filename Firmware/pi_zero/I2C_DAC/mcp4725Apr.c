// mcp4725.c

#include <stdio.h>
#include <sys/types.h>          // open
#include <sys/stat.h>           // open
#include <fcntl.h>              // open
#include <string.h>             //for atoi()
#include <unistd.h>             // read/write usleep
#include <stdlib.h>             // exit
#include <inttypes.h>           // uint8_t, etc
#include <linux/i2c-dev.h>      // I2C bus definitions
#include <sys/ioctl.h>
// Helper function to output DAC value in fast mode
int output_dac_value(int fd, uint16_t value) {
    uint8_t control_byte = 0x40;
    uint8_t data_msb = (value >> 8) & 0x0F; // Only 4 MSBs
    uint8_t data_lsb = value & 0xFF;

    uint8_t buffer[3] = {control_byte, data_msb, data_lsb};

    if (write(fd, buffer, 3) != 3) {
        printf("Error: Failed to write to DAC!\n");
        return -1;
    }
    return 0;

}

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "tusb.h"

bool is_i2c_available(i2c_inst_t *i2c) {
    // Check if the I2C instance is valid
    return (i2c == i2c0 || i2c == i2c1);
}

int main() {
    stdio_init_all();
    //  see https://forums.raspberrypi.com/viewtopic.php?t=300136
    int i = 100;
    while (!tud_cdc_connected() && i--) { sleep_ms(100);  }
    printf("USB_connected\n");

    if (is_i2c_available(i2c0)) {
        printf("I2C0 is available.\n");
    } else {
        printf("I2C0 is not available.\n");
    }

    if (is_i2c_available(i2c1)) {
        printf("I2C1 is available.\n");
    } else {
        printf("I2C1 is not available.\n");
    }

    return 0;
}
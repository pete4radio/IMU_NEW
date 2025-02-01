#include "hardware/i2c.h"
#include "pico/stdlib.h"

// Function to deconfigure the I2C bus
void deconfigure_i2c(i2c_inst_t *i2c) {
    // Deinitialize the I2C instance
    i2c_deinit(i2c);
}

int main() {
    stdio_init_all();

    // Initialize I2C0 with some configuration
    i2c_init(i2c0, 100 * 1000); // 100 kHz
    gpio_set_function(4, GPIO_FUNC_I2C); // SDA
    gpio_set_function(5, GPIO_FUNC_I2C); // SCL
    gpio_pull_up(4);
    gpio_pull_up(5);

    // Use the I2C bus for some operations...

    // Deconfigure the I2C bus
    deconfigure_i2c(i2c0);

    return 0;
}
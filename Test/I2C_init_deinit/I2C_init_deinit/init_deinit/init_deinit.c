#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "tusb.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
//  These are the GPIO numbers not the pin numbers
#define I2C_SDA 4
#define I2C_SCL 5



// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}



int main()
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    
    stdio_init_all();
        //  see https://forums.raspberrypi.com/viewtopic.php?t=300136
    int k = 100;
    while (!tud_cdc_connected() && k--) { sleep_ms(100);  }
    printf("USB_connected\n");

    int j = 10; int i = 10;
    while (1) {
        // I2C Initialisation. Using it at 400Khz.
        i2c_init(I2C_PORT, 400*1000);
        
        gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
        gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
        gpio_pull_up(I2C_SDA);
        gpio_pull_up(I2C_SCL);
        printf("I2C Initialized\n");
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

        i = 10; j = 4;
        while (i--)
        {
            printf(".");
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
            sleep_ms(100);
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            sleep_ms(2000);
        }

        while (j--) {
            printf("\nI2C Bus Scan\n");
            printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

            int ret;
            uint8_t rxdata;
            for (int addr = 0; addr < (1 << 7); ++addr) {
                if (addr % 16 == 0) {
                    printf("%02x ", addr);
                }

                
                if (reserved_addr(addr))
                    ret = PICO_ERROR_GENERIC;
                else
                    ret = i2c_read_blocking_until(i2c0, addr, &rxdata, 1, false, make_timeout_time_ms(100));

                printf(ret < 0 ? "." : "@");
                printf(addr % 16 == 15 ? "\n" : "  ");
            }
        }
    
        // Deconfigure the I2C bus
        i2c_deinit(i2c0);
        printf("I2C Deinitialized\n");
    }
}

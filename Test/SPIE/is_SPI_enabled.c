#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "tusb.h"


int main() {
    stdio_init_all();
    //wait for usb to be connected
    int i = 100;
    while (!tud_cdc_connected() && i > 0) {
        sleep_ms(100);
        i--;
    }
    printf("is_SPI_enabled\n");

    // Initialize SPI interfaces
    spi_init(spi0, 500 * 1000); // Initialize SPI0 at 500 kHz
    spi_init(spi1, 500 * 1000); // Initialize SPI1 at 500 kHz

    // Check availability of SPI interfaces
    bool spi0_available = spi_is_enabled(spi0);
    bool spi1_available = spi_is_enabled(spi1);

    // Print the results
    printf("SPI0 is %s\n", spi0_available ? "available" : "not available");
    printf("SPI1 is %s\n", spi1_available ? "available" : "not available");

    return 0;
}
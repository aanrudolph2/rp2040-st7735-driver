#include "st7735_drv.h"

uint16_t * st7735_screen_buf;

void writeCommand(uint8_t cmd) {
    gpio_put(DC_TFT, 0);
    spi_write_blocking(spi0, &cmd, 1);
}

void writeData(uint8_t data) {
    gpio_put(DC_TFT, 1);
    spi_write_blocking(spi0, &data, 1);
}

void st7735_redraw() {
    dma_channel_wait_for_finish_blocking(0);
    gpio_put(DC_TFT, 1);
    dma_channel_set_read_addr(0, st7735_screen_buf, true);
}

void st7735_init(uint16_t * fb, size_t fb_sz) {

    st7735_screen_buf = fb;

    // Set up SPI
    spi_init(spi_default, 25000000);
    gpio_init(PICO_DEFAULT_SPI_CSN_PIN);

    gpio_set_function(DC_TFT, GPIO_FUNC_SIO);
    gpio_set_function(1, GPIO_FUNC_SPI); // SS
    gpio_set_function(2, GPIO_FUNC_SPI); // SCK
    gpio_set_function(3, GPIO_FUNC_SPI); // MOSI
    gpio_set_function(4, GPIO_FUNC_SPI); // MISO

    // Set up aux pins
    gpio_set_dir(DC_TFT, GPIO_OUT);
    gpio_put(DC_TFT, 0);

    // Init Display
    writeCommand(ST7735_SLPOUT);
    writeCommand(ST7735_COLMOD);
    writeData(0x05);
    writeCommand(ST7735_MADCTL);
    writeData(0xB4);
    /*
    // Offset display window
    writeCommand(ST7735_CASET);
    writeData(0x0); writeData(0x03); // Start X address = 3
    writeData(0x00); writeData(0x83); // End X address = 131
    writeCommand(ST7735_RASET);
    writeData(0x00); writeData(0x00); // Start Y address = 0
    writeData(0x00); writeData(0x80); // End Y address = 128
    */
    writeCommand(ST7735_DISPON);
    busy_wait_ms(100);

	writeCommand(ST7735_RAMWR); // Write to RAM
    gpio_put(DC_TFT, 1);
    
    for (int i = 0; i < fb_sz; i ++)
        st7735_screen_buf[i] = 0x000F;

    // Set up DMA
    dma_channel_config cfg = dma_channel_get_default_config(0);
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_16);
    channel_config_set_read_increment(&cfg, true);
    channel_config_set_write_increment(&cfg, false);
    channel_config_set_dreq(&cfg, DREQ_SPI0_TX);
    
    dma_channel_configure(0, &cfg, &spi_get_hw(spi_default)->dr, st7735_screen_buf, fb_sz, true);

}
#include "st7735_drv/st7735_drv.h"

/*
#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define UARTDR 0x40034000
*/

#define SCREEN_BUF_SIZE 34944

int main() {
    /*
        // Set up our UART with the required speed.
        uart_init(UART_ID, BAUD_RATE);

        // Set the TX and RX pins by using the function select on the GPIO
        // Set datasheet for more information on function select
        gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

        uart_get_hw(UART_ID)->dr; // UART rx/tx register

        uint32_t * uart_reg = (uint32_t*)UARTDR;

        char str[] = "Hello from DMA\r\n";

        dma_channel_config cfg = dma_channel_get_default_config(0);
        channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
        channel_config_set_read_increment(&cfg, true);
        channel_config_set_write_increment(&cfg, false);
        //channel_config_set_dreq(&cfg, DREQ_UART0_TX);

        dma_channel_configure(0, &cfg, uart_reg, str, 16, true);
    */

    uint16_t color = 0x000F;

    uint16_t * screen_buf;
    screen_buf = malloc(SCREEN_BUF_SIZE * sizeof(uint16_t));

    st7735_init(screen_buf, SCREEN_BUF_SIZE);

    while(1) {
        busy_wait_ms(500);
        color ++;
        for (int i = 0; i < SCREEN_BUF_SIZE; i ++)
            screen_buf[i] = color;
        st7735_redraw();
    }
}

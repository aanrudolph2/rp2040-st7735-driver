#include "st7735_drv/st7735_drv.h"
#include "bmp-data.h"

#define SCREEN_BUF_SIZE 20480

int main() {

    uint16_t * screen_buf;
    screen_buf = malloc(SCREEN_BUF_SIZE * sizeof(uint16_t));

    st7735_init(screen_buf, SCREEN_BUF_SIZE);
    for(int i = 0; i < SCREEN_BUF_SIZE; i ++) {
        screen_buf[i] = bmp_data[i];
    }

    st7735_redraw();

    while(1) {
        busy_wait_ms(500);
    }
}

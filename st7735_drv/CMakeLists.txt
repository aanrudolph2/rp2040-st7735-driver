add_library(st7735_drv
    st7735_drv.c
    )

target_link_libraries(st7735_drv pico_stdlib hardware_spi hardware_dma)
target_include_directories (st7735_drv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#include "trap.h"

typedef volatile uint32_t* spi_addr_t;
#define SPI_BASE   (uintptr_t)0x10001000
#define SPI_SS     (spi_addr_t)(SPI_BASE + 0x18)
#define SPI_DIV    (spi_addr_t)(SPI_BASE + 0x14)
#define SPI_CTRL   (spi_addr_t)(SPI_BASE + 0x10)
#define SPI_RX     (spi_addr_t)(SPI_BASE + 0X0)
#define SPI_TX     (spi_addr_t)(SPI_BASE + 0X0)


int main(){
    spi_addr_t ss = SPI_SS, ctrl = SPI_CTRL, divider = SPI_DIV;
    spi_addr_t data; data = SPI_RX;
    *divider = 0b1;
    *ss = 0x80; // select bit rev
    *data = 0b11110000;
    *ctrl = 0;
    *ctrl |= 0x8; // 8bit
    *ctrl |= 1 << 9; // scan on negedge
    *ctrl |= 1 << 8; // go
    volatile uint32_t ctl = 0;
    while (ctl != 0x208){
        print_int(ctl);
        putch('\n');
        ctl = *ctrl;
    }
    *ctrl |= 1 << 8; // go
    putch('\n');
    volatile uint32_t ctl_ = 0;
    while (ctl_ != 0x208){
        print_int(ctl);
        putch('\n');
        ctl_ = *ctrl;
    }
    putch('\n');
    volatile uint32_t a = *data;
    print_int(a);
    for(int i = 0;i < a;i++){

    }
    *data = 0;
    while(1);
    
    return 0;
}
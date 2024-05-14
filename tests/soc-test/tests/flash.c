#include "trap.h"

#define FLASH_BASE (uint8_t*)0x30000000
#define FLASH_SIZE 0x1000000
int main(){
    uint32_t* addr = (uint32_t*) FLASH_BASE;
    for(int off = 0; off < FLASH_SIZE;off++){
        // print_int(*(addr+off));
        // putch('\n');
        panic_on(*(addr+off) != ((uint32_t)(addr+off) & 0xffff),"flash error");
    }
}
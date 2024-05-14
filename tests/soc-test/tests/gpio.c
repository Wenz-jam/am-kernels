#include "trap.h"


#define GPIO_BASE 0x10002000
int main(){
  volatile uint16_t *gpio = (uint16_t *)GPIO_BASE;
  volatile uint16_t *gpio_sw = (uint16_t *)(GPIO_BASE + 0x4);
  volatile uint32_t *gpio_seg = (uint32_t *)(GPIO_BASE + 0x8);
  while (*gpio_sw != 0b1111000011110000);
  *gpio_seg = 0x12345678;
  
  uint16_t a;
  while(1){
    a = 0x1;
    for(int i = 0;i < 16;i++){
      volatile int j = 0;
      while(j < 1000){
        j++;
      }
      *gpio = a;
      a = a << 1;
    }
  }
}
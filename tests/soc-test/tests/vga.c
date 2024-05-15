#include "trap.h"

#define VGA_BASE 0x21000000
#define WIDTH 640
#define HEIGHT 480
#define RGB(r,g,b) ((r << 16) | (g << 8) | b)
int main(){
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      uint8_t r = (x * 255) / WIDTH;
      uint8_t g = (255 * y) / HEIGHT;
      uint8_t b = 255 - ((x * 255) / WIDTH);
      uint32_t color = RGB(r, g, b);
      (y * WIDTH + x)[(uint32_t *)VGA_BASE] = color;
    }
  }
  while (1);
}
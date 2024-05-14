#include <am.h>
#include <klib.h>
#include <klib-macros.h>


static inline uint8_t  inb(uintptr_t addr) { return *(volatile uint8_t  *)addr; }
static inline uint16_t inw(uintptr_t addr) { return *(volatile uint16_t *)addr; }
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }

#define CLINT_BASE_ADDR 0x02000000 + 0XBFF8
void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint64_t us = inl(CLINT_BASE_ADDR + 4);
  us = us << 32 | inl(CLINT_BASE_ADDR);
  uptime->us = us;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}

int main() {
  AM_TIMER_RTC_T rtc = {0};
	AM_TIMER_UPTIME_T uptime = {0};
  int sec = 1;
  while (1) {
    while(uptime.us < sec) __am_timer_uptime(&uptime);
    __am_timer_rtc(&rtc);
		putch('\a');
    sec ++;
  }
}

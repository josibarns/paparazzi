#include "std.h"
#include "init_hw.h"
#include "sys_time.h"
#include "led.h"
#include "interrupt_hw.h"
#include "uart.h"

#include "messages.h"
#include "downlink.h"

static inline void main_init( void );
static inline void main_periodic_task( void );

static uint32_t t0, t1;

int main( void ) {
  main_init();
  while(1) {
    if (sys_time_periodic())
      main_periodic_task();
  }
  return 0;
}

static inline void main_init( void ) {
  hw_init();
  sys_time_init();
  led_init();
  uart0_init_tx();
  int_enable();
}

static inline void main_periodic_task( void ) {
  LED_TOGGLE(1);
  //  DOWNLINK_SEND_TAKEOFF(&cpu_time_sec);
  t0 = T0TC;

  t1 = T0TC;
  uint32_t dif = t1 - t0;
  DOWNLINK_SEND_TIME(&dif);
}

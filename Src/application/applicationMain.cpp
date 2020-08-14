#include "board_api.hpp"

extern "C" void application_entry(void);

void application_entry(void)
{
  board_api::Led led(0);


  while(true)
  {
    led.on();
    board_api::sleep_ms(500);
    led.off();
    board_api::sleep_ms(500);
  }
}

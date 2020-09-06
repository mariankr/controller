#include "board_api.hpp"
#include "debug.hpp"

void application_entry(void)
{
  debug::init();
  board_api::Led led(0);

  while(true)
  {
    led.on();
    board_api::sleep_ms(500);
    led.off();
    board_api::sleep_ms(500);
    const char hello[] = "Hello";
    debug::trace(hello);
    debug::trace("world!\n");
  }
}

#include "boardMain.hpp"
#include "serial.hpp"

extern void application_entry(void);

void board_entry(void)
{
  board_api::comm::initialize();
  application_entry();
}


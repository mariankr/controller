#include "board_api.hpp"

void application_entry(void)
{
  board_api::Led led(0);

  auto* serial = board_api::comm::SerialPort::get(0);
  const board_api::comm::SerialPort::Settings settings = {
    board_api::comm::SerialPort::Baudrate::_115200,
    board_api::comm::SerialPort::Parity::None,
    board_api::comm::SerialPort::StopBits::One
  };
  serial->initialize(settings);
  while(true)
  {
    led.on();
    board_api::sleep_ms(500);
    led.off();
    board_api::sleep_ms(500);
    char text[] = "Hello World!";
    uint32_t to_write = sizeof(text);
    serial->write(text, to_write);
  }
}

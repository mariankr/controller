#include "board_api.hpp"
#include "debug.hpp"

namespace debug
{
  void init()
  {
    auto* serial = board_api::comm::SerialPort::get(0);
    const board_api::comm::SerialPort::Settings settings = {
        board_api::comm::SerialPort::Baudrate::_115200,
        board_api::comm::SerialPort::Parity::None,
        board_api::comm::SerialPort::StopBits::One
    };
    serial->initialize(settings);
    char text[] = "Debug START\n";
    uint32_t to_write = sizeof(text);
    serial->write(text, to_write);
  }

  void trace(const char* ptr, std::size_t sz)
  {
    // TODO: possible loss of data
    auto* serial = board_api::comm::SerialPort::get(0);
    uint32_t to_write = sz;
    serial->write(ptr, to_write);
  }



}
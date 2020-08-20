#include "api/board_api.hpp"
#include "utils/buffer.hpp"
#include "utils/objectBuffer.hpp"
#include "serial.hpp"
#include "main.h"
#include "stm32l4xx_hal.h"

namespace board_api::comm
{
  class SerialPort::Impl
  {
  public:
    Impl() {
      serial_.pImpl_ = this;
    }
    void initialize(Settings settings);
  public:
    SerialPort serial_;
    board::utils::CircularBuffer<uint8_t, 1024> read_buffer_;
    board::utils::CircularBuffer<uint8_t, 256> write_buffer_;
  };
  void SerialPort::Impl::initialize(Settings settings)
  {
  }
}

// same namespace but intellisense is not working if they are merged
namespace board_api::comm
{
  constexpr unsigned PORT_CNT = 1;

  USART_TypeDef* getPort(unsigned aPortNum)
  {
    switch (aPortNum) {
    default:
    case 0:
      return USART1;
    }
  }

  using SerialObjectBuffer = board::utils::ObjectBuffer<SerialPort::Impl>;
  SerialObjectBuffer serialPortImplObjectBuffer;
  SerialPort::Impl* serialPortImplPtr;

  SerialPort* SerialPort::get(unsigned serial_index)
  {
    if (serial_index == 0)
    {
      return &serialPortImplPtr->serial_;
    }
    return nullptr;
  }

  void SerialPort::initialize(SerialPort::Settings settings)
  {
    pImpl_->initialize(settings);
  }

  Status SerialPort::write(const void* buf, uint32_t& len)
  {
    return Status::UnknownError;
  }

  Status SerialPort::read(void* buf, uint32_t& len)
  {
    return Status::UnknownError;
  }

  void initialize()
  {
    serialPortImplPtr = serialPortImplObjectBuffer.construct();
  }

}

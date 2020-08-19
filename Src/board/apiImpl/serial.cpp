#include "api/board_api.hpp"
#include "utils/buffer.hpp"
#include "utils/objectBuffer.hpp"
#include "serial.hpp"

namespace board_api::comm
{
  constexpr unsigned PORT_CNT = 1;
  using SerialBuffer = board::utils::CircularBuffer<uint8_t, 1230>;

  class Serial::Impl
  {
  public:
    Impl() {
      serial_.pImpl_ = this;
    }
  public:
    Serial serial_;
  };

  using SerialObjectBuffer = board::utils::ObjectBuffer<board_api::comm::Serial::Impl>;
  SerialObjectBuffer serialPortImplObjectBuffer;
  board_api::comm::Serial::Impl* serialPortImplPtr;

  Serial* Serial::get(unsigned serial_index)
  {
    return &serialPortImplPtr->serial_;
  }

  Status Serial::initialize(Settings settings)
  {
    return Status::UnknownError;
  }

  Status Serial::write(const void* buf, uint32_t& len)
  {
    return Status::UnknownError;
  }

  Status Serial::read(void* buf, uint32_t& len)
  {
    return Status::UnknownError;
  }

  void initialize()
  {
    serialPortImplPtr = serialPortImplObjectBuffer.construct();
  }
}
#include "api/board_api.hpp"
#include "utils/buffer.hpp"

namespace board_api::comm
{
  using SerialBuffer = board::utils::CircularBuffer<uint8_t, 1230>;

  Serial* Serial::get(unsigned serial_index)
  {
    return nullptr;
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
}
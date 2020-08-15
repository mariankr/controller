#include "board_api.hpp"

namespace board_api::comm
{

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
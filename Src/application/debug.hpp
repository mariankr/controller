#include <cstddef>

namespace debug
{
  constexpr unsigned DEBUG_SERIAL_PORT_INDEX = 0;
  void init();

  void trace(const char*, std::size_t);


  template<std::size_t Size>
  constexpr void trace(const char(&aArray)[Size])
  {
    trace(aArray, Size - 1);
  }
}
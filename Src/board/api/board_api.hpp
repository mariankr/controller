#pragma once
#include <cstdint>

namespace board_api
{
  void sleep_ms(uint32_t milliseconds);

  class Led
  {
  public:
    Led(unsigned number) : number_(number)
    {
      
    }
    void on();
    void off();
  private:
    unsigned number_;
  };

}

#pragma once
#include <stdint.h>

namespace board_api
{
  void sleep_ms(uint32_t milliseconds);

  enum class Status
  {
    Ok,
    SerialTxQueueFull,
    SerialRxQueueEmpty,
    UnknownError
  };

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


  class Keyboard
  {
  public:
    enum class Key : uint8_t
    {
      NONE,
      KEY01
    };
    static Key getKey();
  };

  namespace display
  {
    class Alphanumeric
    {
    public:
      enum class Cursor
      {
        None,
        Underline,
        BlinkingBlock
      };

      using Contrast = uint8_t;

      static void clear();
      static void textOut(uint8_t x, uint8_t y, const char* text);

      struct CursorPosition
      {
        uint8_t x;
        uint8_t y;
      };
      void cursorSet(CursorPosition position);
      void cursorSet(Cursor cursor);
    };
  }

  namespace digital
  {
    class Output
    {
      // TODO: impl
    };

    class Input
    {
      // TODO: impl
    };
  }

  namespace comm
  {
    class SerialPort
    {
    public:
      static constexpr unsigned SERIAL_PORT_COUNT = 1;
      static SerialPort* get(unsigned serial_index);

      //bool waitData(unsigned time_milliseconds);

      enum class Baudrate
      {
        _9600 = 9600,
        _115200 = 115200,
      };

      enum class Parity
      {
        None,
        Odd,
        Even
      };

      enum class StopBits
      {
        One,
        OneAndHalf,
        Two,
      };

      struct Settings
      {
        Baudrate baudrate;
        Parity parity;
        StopBits stop_bits;
      };

      void initialize(Settings settings);
      Status write(const void* buf, uint32_t& len);
      Status read(void* buf, uint32_t& len);
    public:
      class Impl;
    private:
      Impl* pImpl_;
    };
  }
}

#include "api/board_api.hpp"
#include "main.h"
#include "stm32l4xx_hal.h"
#include "utils/buffer.hpp"
#include "utils/objectBuffer.hpp"
#include "serial.hpp"

namespace board_api::comm
{
  USART_TypeDef* getUsart(unsigned serial_port)
  {
    switch (serial_port) {
    default:
    case 0:
      return USART1;
    }
  }

  IRQn_Type getIRQn(unsigned serial_port)
  {
    switch (serial_port) {
    default:
    case 0:
      return USART1_IRQn;
    }
  }

  class SerialPort::Impl
  {
  public:
    Impl(unsigned index) {
      serial_.pImpl_ = this;
      usart_ = getUsart(index);
      usart_index_ = index;
    }
    void initialize(Settings settings);
    SerialPort serial_;
  private:
    board::utils::CircularBuffer<uint8_t, 1024> read_buffer_;
    board::utils::CircularBuffer<uint8_t, 256> write_buffer_;
    Status write(const void* buf, uint32_t& length)
    {
      uint16_t toWrite = length;
      const uint8_t* toSendPtr = static_cast<const uint8_t*>(buf);

      length = 0;
      while (toWrite--) {
        auto byte = *static_cast<const uint8_t*>(toSendPtr);
        if (write_buffer_.put(byte)) {
          length++;
          toSendPtr++;
        }
        else {
          break;
        }
      }

      transmitInterruptEnable();

      if (length == 0) return Status::SerialTxQueueFull;
      return Status::Ok;
    }

    Status read(void* buf, uint32_t& length)
    {
      uint16_t toRead = length;
      uint8_t* toReadPtr = static_cast<uint8_t*>(buf);

      length = 0;
      while (toRead--) {
        auto& byte = *static_cast<uint8_t*>(toReadPtr);
        if (write_buffer_.get(byte)) {
          length++;
          toReadPtr++;
        }
        else {
          break;
        }
      }

      receiveInterruptEnable();

      if (length == 0) return Status::SerialRxQueueEmpty;
      return Status::Ok;
    }

    void transmitInterruptEnable()
    {
      LL_USART_EnableIT_TXE(usart_);
    }
    void transmitInterruptDisable()
    {
      LL_USART_DisableIT_TXE(usart_);
    }
    void receiveInterruptEnable()
    {
      LL_USART_EnableIT_RXNE(usart_);
    }
    void receiveInterruptDisable()
    {
      LL_USART_DisableIT_RXNE(usart_);
    }

  private:
    USART_TypeDef* usart_;
    unsigned usart_index_;
    friend class SerialPort;
  };
  void SerialPort::Impl::initialize(Settings settings)
  {
    LL_USART_InitTypeDef USART_InitStruct = {};

    USART_InitStruct.BaudRate = static_cast<uint32_t>(settings.baudrate);
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;

    switch (settings.parity)
    {
    default:
    case Parity::None:
      USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
      USART_InitStruct.Parity = LL_USART_PARITY_NONE;
      break;
    case Parity::Odd:
      USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_9B;
      USART_InitStruct.Parity = LL_USART_PARITY_ODD;
      break;
    case Parity::Even:
      USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_9B;
      USART_InitStruct.Parity = LL_USART_PARITY_EVEN;
      break;
    }

    switch (settings.stop_bits)
    {
    default:
    case StopBits::One:
      USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
      break;
    case StopBits::OneAndHalf:
      USART_InitStruct.StopBits = LL_USART_STOPBITS_1_5;
      break;
    case StopBits::Two:
      USART_InitStruct.StopBits = LL_USART_STOPBITS_2;
      break;
    }
    LL_USART_Disable(usart_);
    LL_USART_Init(usart_, &USART_InitStruct);
    LL_USART_ConfigAsyncMode(usart_);
    LL_USART_Enable(usart_);
    NVIC_EnableIRQ(getIRQn(usart_index_));
    
    receiveInterruptEnable();
  }
}

// same namespace but intellisense is not working if they are merged
namespace board_api::comm
{
  constexpr unsigned PORT_CNT = 1;

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

  Status SerialPort::write(const void* buf, uint32_t& length)
  {
    return pImpl_->write(buf, length);
  }

  Status SerialPort::read(void* buf, uint32_t& length)
  {
    return pImpl_->read(buf, length);
  }

  void initialize()
  {
    serialPortImplPtr = serialPortImplObjectBuffer.construct(0);
  }

}

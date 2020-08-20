#include <stdint.h>
#include <atomic>
#include <array>

namespace board::utils
{

  template<class T, uint32_t SIZE>
  class CircularBuffer
  {
  public:
    static_assert(sizeof(T) <= 4, "change put, pass argument by reference");
    bool put(const T data); 
    bool get(T& data);
    void clear() {
      read_pos_ = write_pos_ = 0;
    }

  private:
    std::atomic<uint32_t> read_pos_;
    std::atomic<uint32_t> write_pos_;
    std::array<uint8_t, SIZE> data_;
  };


  template<class T, uint32_t SIZE>
  inline bool CircularBuffer<T, SIZE>::put(const T data)
  {
    const auto new_write_pos = (write_pos_ + 1) % SIZE;
    if (new_write_pos == read_pos_) {
      return false; // full
    }
    data_[new_write_pos] = data;
    write_pos_ = new_write_pos;
    return true;
  }

  template<class T, uint32_t SIZE>
  inline bool CircularBuffer<T, SIZE>::get(T& data)
  {
    if (read_pos_ == write_pos_) {
      return false; // empty
    }
    data = data_[read_pos_];
    const auto new_read_pos = (read_pos_ + 1) % SIZE;
    read_pos_ = new_read_pos;
    return true;
  }



}
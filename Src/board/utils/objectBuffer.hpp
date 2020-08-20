#pragma once

#include <stdint.h>
#include <new> // placement new

namespace board::utils
{
  template<class T>
  class ObjectBuffer
  {
  public:
    static constexpr auto SIZE = sizeof(T);

    template<typename... Args>
    T* construct(Args&&... args)
    {
      return new (buf) T(args...);
    }

    void destruct()
    {
      reinterpret_cast<T*>(buf)->~T();
    }

  private:
    alignas(8) uint8_t buf[SIZE];
  };

  namespace usage
  {
    class X
    {
    public:
      X() : x(1), ptr("Constructor X()")
      {
      }
      X(int i) : x(i), ptr("Constructor X(int)")
      {
      }
      X(int i, int j) : x(i + j), ptr("Constructor X(int, int)")
      {
      }

    private:
      unsigned x;
      const char* ptr;
    };
    void usage()
    {
      using BuferForX = ObjectBuffer<X>;
      BuferForX xbuf, ybuf, zbuf;
      X* x = xbuf.construct(); // runs constructor X()
      X* y = ybuf.construct(1); // runs constructor X(int)
      X* z = zbuf.construct(1, 2); // runs constructor X(int, int)

      x->~X();
      y->~X();
      z->~X();
    }
  }

}
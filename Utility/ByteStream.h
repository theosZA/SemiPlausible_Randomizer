#pragma once

#include <cstdint>
#include <iosfwd>

// Wrapper around a stream that allows you to serialize data as a sequence of bytes.
// Little-endian order is used.
class ByteStream
{
public:
  ByteStream(std::ostream& out) : out(out) {}

  template <typename T>
  ByteStream& operator<<(const T& value)
  {
    for (size_t i = 0; i < sizeof(T); ++i)
      out << static_cast<std::uint8_t>(value >> (8 * i));
    return *this;
  }

private:
  std::ostream& out;
};
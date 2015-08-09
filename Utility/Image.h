#pragma once

#include <array>
#include <cstdint>
#include <fstream>

#include "Utility\ByteStream.h"

// A simple bitmap image with pre-defined width and height.
template<size_t width, size_t height>
class Image
{
public:
  // Clears the image, replacing all pixels with the given colour.
  void Clear(std::uint32_t backgroundColour);
  void Clear(int r, int g, int b);

  // Writes the image in TGA file format.
  void WriteTgaFile(const std::string& fileName) const;

private:
  std::array<std::array<std::uint32_t, width>, height> bitmap;
};

template<size_t width, size_t height>
inline void Image<width, height>::Clear(std::uint32_t backgroundColour)
{
  for (size_t y = 0; y < height; ++y)
    for (size_t x = 0; x < width; ++x)
      bitmap[y][x] = backgroundColour;
}

template<size_t width, size_t height>
inline void Image<width, height>::Clear(int r, int g, int b)
{
  Clear(static_cast<std::uint32_t>(r) << 16 | static_cast<std::uint32_t>(g) << 8 | static_cast<std::uint32_t>(b));
}

template<size_t width, size_t height>
inline void Image<width, height>::WriteTgaFile(const std::string& fileName) const
{
  std::ofstream out(fileName, std::ios::binary);
  ByteStream bytes(out);
  bytes << std::uint8_t(0);   // image ID field length
  bytes << std::uint8_t(0);   // no colour map used
  bytes << std::uint8_t(10);  // run-length encoded true-colour image
  bytes << std::uint16_t(0) << std::uint16_t(0) << std::uint8_t(0);   // colour map specification N/A
  bytes << std::uint16_t(0);  // x origin  
  bytes << std::uint16_t(0);  // y origin
  bytes << std::uint16_t(width);  // width
  bytes << std::uint16_t(height); // height
  bytes << std::uint8_t(24);  // bits per pixel
  bytes << std::uint8_t(0);   // image descriptor (alpha bits + direction)

  auto writeRun = 
      [&](int run, std::uint32_t colour)
      {
        bytes << static_cast<std::uint8_t>((run - 1) | 0x80)
              << static_cast<std::uint8_t>(colour)        // b
              << static_cast<std::uint8_t>(colour >> 8)   // g
              << static_cast<std::uint8_t>(colour >> 16); // r
      };

  for (size_t y = 0; y < height; ++y)
  {
    std::uint32_t currentColour = 0;
    int sameColourCount = 0;
    for (size_t x = 0; x < width; ++x)
    {
      if (sameColourCount == 0)
      {
        currentColour = bitmap[y][x];
        sameColourCount = 1;
      }
      else if (currentColour == bitmap[y][x])
      {
        ++sameColourCount;
        if (sameColourCount == 128) // max RLE length
        {
          writeRun(sameColourCount, currentColour);
          sameColourCount = 0;
        }
      }
      else // run has ended
      {
        writeRun(sameColourCount, currentColour);
        currentColour = bitmap[y][x];
        sameColourCount = 1;
      }
    }
    if (sameColourCount > 0)
      writeRun(sameColourCount, currentColour);
  }
}

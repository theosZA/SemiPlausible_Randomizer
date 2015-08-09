#pragma once

#include <random>

// Uniform random generator.
class Random
{
public:
  Random()
  : engine(std::random_device()())
  {}

  template <typename IntegerType = int>
  IntegerType GetRandomValue(IntegerType min, IntegerType max)
  {
    return std::uniform_int<IntegerType>(min, max)(engine);
  }

private:
  std::mt19937 engine;
};

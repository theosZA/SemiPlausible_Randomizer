#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>

#include <ParadoxNode\ParadoxNode.h>

#include "Config.h"
#include "EU4\ProvinceIDCollection.h"
#include "EU4\RegionCollection.h"

std::string ReadFile(const char* fileName)
{
  FILE* file = fopen(fileName, "r");
  if (!file)
    throw std::runtime_error("Failed to open file " + std::string(fileName));

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  char* buffer = new char[size];
  rewind(file);

  fread(buffer, sizeof(char), size, file);
  std::string content(buffer, size);

  delete[] buffer;
  return content;
}

auto ReadParadoxFile(const std::string& fileName)
{
  auto separator = fileName.find_last_of('\\');
  auto sourceFileName = (separator == std::string::npos ? fileName : fileName.substr(separator + 1));

  return ParadoxNode::Parse(ReadFile(fileName.c_str()), sourceFileName);
}

int main(int argc, char** argv)
{
  try
  {
    Config config(*ReadParadoxFile("config.txt"));

    EU4::RegionCollection regions(*ReadParadoxFile(config.GetEU4Path() + "map\\region.txt"));
    
    EU4::ProvinceIDCollection generateProvinces;
    for (const auto& provinceID : config.GetProvincesToGenerate())
      generateProvinces.AddProvince(provinceID);
    for (const auto& regionName : config.GetRegionsToGenerate())
      generateProvinces.AddRegion(regions, regionName);

    std::cout << "Generating for provinces: " << generateProvinces << '\n';
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}
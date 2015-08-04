#include <iostream>
#include <stdexcept>
#include <string>

#include <ParadoxNode\ParadoxNode.h>

#include "Config.h"
#include "EU4\ProvinceIDCollection.h"
#include "EU4\RegionCollection.h"

int main(int argc, char** argv)
{
  try
  {
    Config config(*ParadoxNode::ParseFromFile("config.txt"));

    EU4::RegionCollection regions(*ParadoxNode::ParseFromFile(config.GetEU4Path() + "map\\region.txt"));
    
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
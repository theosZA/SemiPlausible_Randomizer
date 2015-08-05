#include <iostream>
#include <stdexcept>
#include <string>

#include <ParadoxNode\ParadoxNode.h>

#include "Config.h"
#include "EU4\ProvinceCollection.h"
#include "EU4\ProvinceIDCollection.h"
#include "EU4\RegionCollection.h"
#include "Mod.h"

int main(int argc, char** argv)
{
  try
  {
    Config config(*ParadoxNode::ParseFromFile("config.txt"));

    EU4::RegionCollection regions(*ParadoxNode::ParseFromFile(config.GetEU4Path() + "map\\region.txt"));
    
    EU4::ProvinceIDCollection generateProvinceIDs;
    for (const auto& provinceID : config.GetProvincesToGenerate())
      generateProvinceIDs.AddProvince(provinceID);
    for (const auto& regionName : config.GetRegionsToGenerate())
      generateProvinceIDs.AddRegion(regions, regionName);

    std::cout << "Generating for provinces: " << generateProvinceIDs << '\n';

    EU4::ProvinceCollection provinces(generateProvinceIDs.GetProvinceIDs(), config.GetEU4Path() + "history\\provinces\\");
    provinces.ClearTags();

    for (auto provinceID : generateProvinceIDs.GetProvinceIDs())
      provinces.SetFullOWner(provinceID, "CAN");

    Mod mod(config.GetModName(), provinces);
    mod.WriteMod(config.GetEU4Path() + "mod\\");
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}
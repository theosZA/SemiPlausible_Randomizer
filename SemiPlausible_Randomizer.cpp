#include <iostream>
#include <stdexcept>
#include <string>

#include <ParadoxNode\ParadoxNode.h>

#include "Config.h"
#include "EU4\ProvinceCollection.h"
#include "EU4\ProvinceIDCollection.h"
#include "EU4\RegionCollection.h"
#include "Mod.h"
#include "ProtoCountryCollection.h"
#include "Utility\Log.h"
#include "Utility\Random.h"

int main(int argc, char** argv)
{
  try
  {
    Random random;
    Config config(*ParadoxNode::ParseFromFile("config.txt"));

    EU4::RegionCollection regions(*ParadoxNode::ParseFromFile(config.GetEU4Path() + "map\\region.txt"));

    LOG(LogLevel::Info) << "Determining generate area";
    EU4::ProvinceIDCollection generateProvinceIDs;
    for (const auto& provinceID : config.GetProvincesToGenerate())
      generateProvinceIDs.AddProvince(provinceID);
    for (const auto& regionName : config.GetRegionsToGenerate())
      generateProvinceIDs.AddRegion(regions, regionName);
    LOG(LogLevel::Debug) << "Generate provinces: " << generateProvinceIDs;

    LOG(LogLevel::Info) << "Reading EU4 provinces";
    EU4::ProvinceCollection provinces(generateProvinceIDs.GetProvinceIDs(), config.GetEU4Path() + "history\\provinces\\");
    provinces.ClearTags();

    EU4::CountryCollection countries;

    ProtoCountryCollection protoCountries;
    LOG(LogLevel::Info) << "Generating proto-countries";
    protoCountries.GenerateFromProvinces(provinces, generateProvinceIDs.GetProvinceIDs(), random);
    LOG(LogLevel::Info) << "Creating countries";
    protoCountries.CreateCountries(countries, random);

    LOG(LogLevel::Info) << "Writing mod";
    Mod mod(config.GetModName(), countries, provinces);
    mod.WriteMod(config.GetEU4Path() + "mod\\");
  }
  catch (std::exception& e)
  {
    LOG(LogLevel::Error) << e.what();
  }
}
#pragma once

#include <set>
#include <vector>

#include "ProtoCountry.h"

namespace EU4 {
class CountryCollection;
class ProvinceCollection;
} // namespace EU4

class Random;
class TagProvinceNameMapping;

// Holds all proto-countries each of them being formed province
// by province from the province IDs provided.
class ProtoCountryCollection
{
public:
  // Creates proto-countries from the specified provinces.
  void GenerateFromProvinces(EU4::ProvinceCollection&, std::set<int> provinceIDs, Random&);

  // Chooses existing countries or creates new countries from the proto-countries with
  // appropriate tags and adds new ones to the given collection.
  void CreateCountries(EU4::CountryCollection&, TagProvinceNameMapping&, Random&);

private:
  std::vector<ProtoCountry> protoCountries;
};
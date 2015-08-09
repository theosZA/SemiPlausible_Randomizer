#pragma once

#include <set>
#include <vector>

#include "ProtoCountry.h"

namespace EU4 {
class CountryCollection;
class ProvinceCollection;
} // namespace EU4

class Random;
// Holds all proto-countries each of them being formed province
// by province from the province IDs provided.
class ProtoCountryCollection
{
public:
  // Creates proto-countries from the specified provinces.
  void GenerateFromProvinces(EU4::ProvinceCollection&, std::set<int> provinceIDs, Random&);

  // Creates new countries from the proto-countries with appropriate tags and adds them to the given collection.
  void CreateCountries(EU4::CountryCollection&, Random&);

private:
  std::vector<ProtoCountry> protoCountries;
};
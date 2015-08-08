#pragma once

#include <set>
#include <vector>

#include "EU4\CountryCollection.h"
#include "EU4\ProvinceCollection.h"
#include "ProtoCountry.h"

// Holds all proto-countries each of them being formed province
// by province from the province IDs provided.
class ProtoCountryCollection
{
public:
  // Creates proto-countries from the specified provinces.
  void GenerateFromProvinces(EU4::ProvinceCollection&, std::set<int> provinceIDs);

  // Creates new countries from the proto-countries with appropriate tags and adds them to the given collection.
  void CreateCountries(EU4::CountryCollection&);

private:
  std::vector<ProtoCountry> protoCountries;
};
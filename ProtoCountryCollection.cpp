#include "ProtoCountryCollection.h"

void ProtoCountryCollection::GenerateFromProvinces(EU4::ProvinceCollection& provinces, std::set<int> provinceIDs)
{
  // For now we're going to just create single province countries.
  for (auto provinceID : provinceIDs)
    protoCountries.emplace_back(provinces, provinceID);
}

void ProtoCountryCollection::CreateCountries(EU4::CountryCollection& countries)
{
  for (auto& protoCountry : protoCountries)
    protoCountry.CreateCountry(countries);
}

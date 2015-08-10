#include "ProtoCountryCollection.h"

#include "Utility\Random.h"

void ProtoCountryCollection::GenerateFromProvinces(EU4::ProvinceCollection& provinces, std::set<int> provinceIDs, Random& random)
{
  while (!provinceIDs.empty())
  {
    auto provinceIndex = random.GetRandomValue<size_t>(0, provinceIDs.size() - 1);
    auto provinceIter = provinceIDs.begin();
    std::advance(provinceIter, provinceIndex);
    auto startingProvinceID = *provinceIter;
    // For now we're going to just create single province countries.
    protoCountries.emplace_back(provinces, startingProvinceID);
    provinceIDs.erase(startingProvinceID);
  }
}

void ProtoCountryCollection::CreateCountries(EU4::CountryCollection& countries, TagProvinceNameMapping& tagProvinceNameMapping, Random& random)
{
  for (auto& protoCountry : protoCountries)
    protoCountry.ChooseOrCreateCountryFromCapital(countries, tagProvinceNameMapping, random);
}

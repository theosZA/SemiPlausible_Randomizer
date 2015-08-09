#pragma once

#include <string>

namespace EU4 {
class CountryCollection;
class ProvinceCollection;
} // namespace EU4

class Random;

// A proto-country is an EU4 country being formed province by province.
class ProtoCountry
{
public:
  // Constructor takes in the ID of the starting province.
  ProtoCountry(EU4::ProvinceCollection&, int startingProvinceID);

  // Creates a new country with an appropriate tag, adding it to the given collection.
  void CreateCountry(EU4::CountryCollection&, Random&);

private:
  std::string DetermineReligion() const;
  std::string DeterminePrimaryCulture() const;

  EU4::ProvinceCollection& provinces;

  std::string tag;
  int provinceID;
};
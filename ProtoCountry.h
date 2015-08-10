#pragma once

#include <string>

namespace EU4 {
class CountryCollection;
class ProvinceCollection;
} // namespace EU4

class Random;
class TagProvinceNameMapping;

// A proto-country is an EU4 country being formed province by province.
class ProtoCountry
{
public:
  // Constructor takes in the ID of the starting province.
  ProtoCountry(EU4::ProvinceCollection&, int startingProvinceID);

  // Chooses an existing country or creates a new country with an appropriate tag matching the capital
  // province, and adding it to the given collection.
  void ChooseOrCreateCountryFromCapital(EU4::CountryCollection&, TagProvinceNameMapping&, Random&);

private:
  int DetermineCapitalProvince() const;
  std::string DetermineReligion() const;
  std::string DeterminePrimaryCulture() const;

  // Sets the owner of all this country's provinces to this country.
  void SetFullOwner();

  EU4::ProvinceCollection& provinces;

  std::string tag;
  int provinceID;
};
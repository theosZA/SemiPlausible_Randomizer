#include "ProtoCountry.h"

ProtoCountry::ProtoCountry(EU4::ProvinceCollection& provinces, int startingProvinceID)
: provinceID(startingProvinceID),
  provinces(provinces)
{}

void ProtoCountry::CreateCountry(EU4::CountryCollection& countries)
{
  tag = countries.AddNewCountry(provinces.GetProvince(provinceID), DetermineReligion(), DeterminePrimaryCulture());
  provinces.GetProvince(provinceID).SetFullOWner(tag);
}

std::string ProtoCountry::DetermineReligion() const
{
  return provinces.GetProvince(provinceID).GetReligion();
}

std::string ProtoCountry::DeterminePrimaryCulture() const
{
  return provinces.GetProvince(provinceID).GetCulture();
}

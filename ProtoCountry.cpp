#include "ProtoCountry.h"

#include "EU4\CountryCollection.h"
#include "EU4\ProvinceCollection.h"
#include "Utility\Log.h"

ProtoCountry::ProtoCountry(EU4::ProvinceCollection& provinces, int startingProvinceID)
: provinceID(startingProvinceID),
  provinces(provinces)
{
  LOG(LogLevel::Debug) << "Creating new proto-country starting from province " << provinceID;
}

void ProtoCountry::CreateCountry(EU4::CountryCollection& countries, Random& random)
{
  tag = countries.AddNewCountry(provinces.GetProvince(provinceID), DetermineReligion(), DeterminePrimaryCulture(), random);
  provinces.GetProvince(provinceID).SetFullOWner(tag);

  LOG(LogLevel::Debug) << "Created new country " << tag << " - " << countries.GetCountry(tag).GetName();
}

std::string ProtoCountry::DetermineReligion() const
{
  return provinces.GetProvince(provinceID).GetReligion();
}

std::string ProtoCountry::DeterminePrimaryCulture() const
{
  return provinces.GetProvince(provinceID).GetCulture();
}

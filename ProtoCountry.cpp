#include "ProtoCountry.h"

#include "EU4\CountryCollection.h"
#include "EU4\ProvinceCollection.h"
#include "TagProvinceNameMapping.h"
#include "Utility\Log.h"

ProtoCountry::ProtoCountry(EU4::ProvinceCollection& provinces, int startingProvinceID)
: provinceID(startingProvinceID),
  provinces(provinces)
{
  LOG(LogLevel::Debug) << "Creating new proto-country starting from province " << provinceID;
}

void ProtoCountry::ChooseOrCreateCountryFromCapital(EU4::CountryCollection& countries, TagProvinceNameMapping& tagProvinceNameMapping, Random& random)
{
  const auto& capital = provinces.GetProvince(DetermineCapitalProvince());

  tag = tagProvinceNameMapping.GetTagForProvince(capital.GetID());
  if (!tag.empty())
  {
    LOG(LogLevel::Debug) << "Using existing tag " << tag << " based on capital province " << capital.GetName();
  }
  else
  {
    tag = countries.AddNewCountry(capital, DetermineReligion(), DeterminePrimaryCulture(), random);
    LOG(LogLevel::Debug) << "Created new country " << tag << " - " << countries.GetCountry(tag).GetName();
  }

  SetFullOwner();
}

int ProtoCountry::DetermineCapitalProvince() const
{
  return provinceID;
}

std::string ProtoCountry::DetermineReligion() const
{
  return provinces.GetProvince(provinceID).GetReligion();
}

std::string ProtoCountry::DeterminePrimaryCulture() const
{
  return provinces.GetProvince(provinceID).GetCulture();
}

void ProtoCountry::SetFullOwner()
{
  provinces.GetProvince(provinceID).SetFullOWner(tag);
}

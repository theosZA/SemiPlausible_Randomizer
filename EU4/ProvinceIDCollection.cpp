#include "ProvinceIDCollection.h"

#include "EU4\RegionCollection.h"

namespace EU4 {

void ProvinceIDCollection::AddProvince(int provinceID)
{
  provinces.insert(provinceID);
}

void ProvinceIDCollection::AddRegion(RegionCollection& regions, const std::string& regionName)
{
  const auto& regionProvinces = regions.GetProvinces(regionName);
  provinces.insert(regionProvinces.begin(), regionProvinces.end());
}

std::ostream& operator<<(std::ostream& out, const ProvinceIDCollection& provinceIDCollection)
{
  for (auto provinceIter = provinceIDCollection.provinces.begin(); provinceIter != provinceIDCollection.provinces.end(); ++provinceIter)
  {
    if (provinceIter != provinceIDCollection.provinces.begin())
      out << ' ';
    out << *provinceIter;
  }
  return out;
}

} // namespace EU4

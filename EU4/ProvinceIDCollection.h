#pragma once

#include <iosfwd>
#include <set>

namespace EU4 {

class RegionCollection;

class ProvinceIDCollection
{
public:
  void AddProvince(int provinceID);
  void AddRegion(RegionCollection&, const std::string& regionName);

  const std::set<int>& GetProvinceIDs() { return provinces; }

  friend std::ostream& operator<<(std::ostream& out, const ProvinceIDCollection&);

private:
  std::set<int> provinces;
};

} // namespace EU4

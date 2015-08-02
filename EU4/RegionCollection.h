#pragma once

#include <map>

#include "EU4\Region.h"

class ParadoxNode;

namespace EU4 {

class RegionCollection
{
public:
  RegionCollection(const ParadoxNode&);

  const std::vector<int>& GetProvinces(const std::string& regionName) const;

private:
  std::map<std::string, Region> regions;
};

} // namespace EU4
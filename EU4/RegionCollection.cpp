#include "RegionCollection.h"

#include <stdexcept>

#include <ParadoxNode\ParadoxNode.h>

namespace EU4 {

RegionCollection::RegionCollection(const ParadoxNode& node)
{
  for (const auto& child : node.GetChildren())
    regions.emplace(child->GetKey(), *child);
}

const std::vector<int>& RegionCollection::GetProvinces(const std::string & regionName) const
{
  auto findIter = regions.find(regionName);
  if (findIter == regions.end())
    throw std::runtime_error("Region " + regionName + " not found");
  return findIter->second.GetProvinces();
}

} // namespace EU4
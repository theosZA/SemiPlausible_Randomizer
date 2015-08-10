#include "TagProvinceNameMapping.h"

#include <ParadoxNode\ParadoxNode.h>

TagProvinceNameMapping::TagProvinceNameMapping(const ParadoxNode& rootNode)
{
  for (const auto& childNode : rootNode.GetChildren())
  {
    auto tag = childNode->GetKey();
    auto provinceID = std::stoi(childNode->GetValue());
    tagsByProvinceID.emplace(provinceID, tag);
  }
}

std::string TagProvinceNameMapping::GetTagForProvince(int provinceID) const
{
  auto findIter = tagsByProvinceID.find(provinceID);
  if (findIter == tagsByProvinceID.end())
    return std::string();
  return findIter->second;
}

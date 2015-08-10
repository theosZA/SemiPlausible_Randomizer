#pragma once

#include <map>
#include <string>

class ParadoxNode;

// Mapping from tags to provinces where the country name is
// derived from the province name
class TagProvinceNameMapping
{
public:
  TagProvinceNameMapping(const ParadoxNode&);

  // Returns the tag associated with the specified province.
  // If there is no such tag, then an empty string is returned instead.
  std::string GetTagForProvince(int provinceID) const;

private:
  std::map<int, std::string> tagsByProvinceID;
};
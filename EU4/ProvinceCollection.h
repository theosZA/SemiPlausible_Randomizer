#pragma once

#include <map>
#include <set>
#include <string>

#include "EU4\Province.h"

namespace EU4 {

class ProvinceCollection
{
  public:
    // Constructor creates all EU4 provinces from the specified set of province IDs.
    ProvinceCollection(const std::set<int>& provinceIDs, const std::string& provincesHistoryPath);

    // Removes all cores, owners and controllers from all provinces in the collection.
    void ClearTags();

  private:
    std::map<int, Province> provinces;
    std::map<int, std::string> provinceHistoryFileNames;
};

} // EU4
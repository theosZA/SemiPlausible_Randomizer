#pragma once

#include <string>
#include <vector>

class ParadoxNode;

namespace EU4 {

// Am EU4 region is a named collection of provinces.
class Region
{
public:
  Region(const ParadoxNode&);

  const std::vector<int>& GetProvinces() const { return provinces; }

private:
  std::string name;
  std::vector<int> provinces;
};

} // namespace EU4
#include "Region.h"

#include <algorithm>

#include <ParadoxNode\ParadoxNode.h>

namespace EU4 {

Region::Region(const ParadoxNode& node)
: name(node.GetKey()),
  provinces(node.GetValues())
{
  std::sort(provinces.begin(), provinces.end());
}

} // namespace EU4
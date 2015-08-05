#include "Config.h"

#include <algorithm>

#include <ParadoxNode\ParadoxNode.h>

Config::Config(const ParadoxNode& node)
: modName(node.GetChild("Output")->GetValue()),
  eu4Path(node.GetChild("EU4Path")->GetValue())
{
  // Paths must end in a backslash.
  if (!eu4Path.empty() && eu4Path.back() != '\\')
    eu4Path.push_back('\\');

  // Read generating region.
  auto generateRoot = node.GetChild("generate");
  if (generateRoot)
  {
    const auto& generateNodes = generateRoot->GetChildren();
    for (const auto& generateNode : generateNodes)
    {
      if (generateNode->GetKey() == "region")
        generateRegions.push_back(generateNode->GetValue());
      else if (generateNode->GetKey() == "province")
        generateProvinces.push_back(std::stoi(generateNode->GetValue()));
      else if (generateNode->GetKey() == "provinces")
        generateProvinces.insert(generateProvinces.end(), generateNode->GetValues().begin(), generateNode->GetValues().end());
    }
    std::sort(generateRegions.begin(), generateRegions.end());
    std::sort(generateProvinces.begin(), generateProvinces.end());
  }
}

#include "Country.h"

#include <fstream>
#include <random>

#include <ParadoxNode\ParadoxNode.h>

#include "Province.h"
#include "Utility\Random.h"

namespace EU4 {

Country::Country(std::string tag, const Province& province, std::string religion, std::string primaryCulture, Random& random)
: tag(std::move(tag)),
  name(province.GetName()),
  adjective(province.GetAdjective()),
  graphicalCulture("westerngfx"),
  government("feudal_monarchy"),
  techGroup("western"),
  religion(std::move(religion)),
  primaryCulture(std::move(primaryCulture)),
  capitalProvince(province.GetID())
{
  for (int i = 0; i < 3; ++i)
    colour.push_back(random.GetRandomValue(0, 255));
  flag.Clear(colour[0], colour[1], colour[2]);
}

std::shared_ptr<ParadoxNode> Country::CreateCommonNode() const
{
  auto commonNode = ParadoxNode::CreateRoot();
  commonNode->AddChild(ParadoxNode::Create("graphical_culture", graphicalCulture));
  commonNode->AddChild(ParadoxNode::Create("color", colour));
  return commonNode;
}

std::shared_ptr<ParadoxNode> Country::CreateHistoryNode() const
{
  auto historyNode = ParadoxNode::CreateRoot();
  historyNode->AddChild(ParadoxNode::Create("government", government));
  historyNode->AddChild(ParadoxNode::Create("technology_group", techGroup));
  historyNode->AddChild(ParadoxNode::Create("religion", religion));
  historyNode->AddChild(ParadoxNode::Create("primary_culture", primaryCulture));
  return historyNode;
}

void Country::WriteFlagFile(const std::string& fileName) const
{
  flag.WriteTgaFile(fileName);
}

} // namespace EU4
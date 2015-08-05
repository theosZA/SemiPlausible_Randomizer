#include "Province.h"

#include <ParadoxNode\ParadoxNode.h>

namespace EU4 {

Province::Province(int id, const std::string& name, const ParadoxNode& history)
: id(id), name(name), hre(false), baseTax(0), baseProduction(0), baseManpower(0), extraCost(0)
{
  for (const auto& item : history.GetChildren())
  {
    if (item->GetKey() == "owner")
      ownerTag = item->GetValue();
    else if (item->GetKey() == "controller")
      controllerTag = item->GetValue();
    else if (item->GetKey() == "add_core")
      coreTags.insert(item->GetValue());
    else if (item->GetKey() == "culture")
      culture = item->GetValue();
    else if (item->GetKey() == "religion")
      religion = item->GetValue();
    else if (item->GetKey() == "hre")
      hre = (item->GetValue() == "yes");
    else if (item->GetKey() == "base_tax")
      baseTax = std::stoi(item->GetValue());
    else if (item->GetKey() == "base_production")
      baseProduction = std::stoi(item->GetValue());
    else if (item->GetKey() == "base_manpower")
      baseManpower = std::stoi(item->GetValue());
    else if (item->GetKey() == "capital")
      capital = item->GetValue();
    else if (item->GetKey() == "extra_cost")
      extraCost = std::stoi(item->GetValue());
    else if (item->GetKey() == "trade_goods")
      tradeGood = item->GetValue();
    else if (item->GetKey() == "discovered_by")
      discoveredByTechGroups.insert(item->GetValue());
    else if (!item->GetChildren().empty() && item->GetChildren()[0]->GetKey() == "add_permanent_province_modifier")
    {
      const auto& modifiers = item->GetChildren()[0]->GetChildren();
      for (const auto& modifier : modifiers)
        if (modifier->GetKey() == "name")
          permanentModifiers.insert(modifier->GetValue());
    }
  }
}

void Province::ClearTags()
{
  ownerTag.clear();
  controllerTag.clear();
  coreTags.clear();  
}

void Province::SetFullOWner(const std::string& tag)
{
  ownerTag = tag;
  controllerTag = tag;
  coreTags.insert(tag);
}

std::shared_ptr<ParadoxNode> Province::CreateHistoryNode() const
{
  auto history = ParadoxNode::CreateRoot();
  if (!ownerTag.empty())
    history->AddChild(ParadoxNode::Create("owner", ownerTag));
  if (!controllerTag.empty())
    history->AddChild(ParadoxNode::Create("controller", controllerTag));
  for (const auto& coreTag : coreTags)
    history->AddChild(ParadoxNode::Create("add_core", coreTag));
  history->AddChild(ParadoxNode::Create("culture", culture));
  history->AddChild(ParadoxNode::Create("religion", religion));
  history->AddChild(ParadoxNode::Create("hre", (hre ? "yes" : "no")));
  history->AddChild(ParadoxNode::Create("base_tax", std::to_string(baseTax)));
  history->AddChild(ParadoxNode::Create("base_production", std::to_string(baseProduction)));
  history->AddChild(ParadoxNode::Create("base_manpower", std::to_string(baseManpower)));
  history->AddChild(ParadoxNode::Create("trade_goods", tradeGood));
  history->AddChild(ParadoxNode::Create("capital", capital));
  if (extraCost != 0)
    history->AddChild(ParadoxNode::Create("extra_cost", std::to_string(extraCost)));
  for (const auto& techGroup : discoveredByTechGroups)
    history->AddChild(ParadoxNode::Create("discovered_by", techGroup));

  for (const auto& permanentModifier : permanentModifiers)
  {
    auto modifierNode = ParadoxNode::Create("add_permanent_province_modifier");
    modifierNode->AddChild(ParadoxNode::Create("name", permanentModifier));
    modifierNode->AddChild(ParadoxNode::Create("duration", "-1"));
    history->AddChild(ParadoxNode::Create("100.1.1", std::vector<std::shared_ptr<ParadoxNode>>({ modifierNode })));
  }

  return history;
}

} // EU4
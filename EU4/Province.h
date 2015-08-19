#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>

class ParadoxNode;

namespace EU4 {

// An EU4 province is a single settled province on the map.
class Province
{
public:
  // Constructor based on an existing EU4 province history.
  Province(int id, std::string name, std::string adjective, std::map<std::string, std::string> culturalNames, const ParadoxNode& history);

  int GetID() const { return id; }
  const std::string& GetName(const std::string& culture = "") const;
  const std::string& GetAdjective() const { return adjective; }
  const std::string& GetCulture() const { return culture; }
  const std::string& GetReligion() const { return religion; }

  // Removes all cores, owner and controller.
  void ClearTags();
  // Sets the given tag as owner and controller and givens them a core on the province.
  void SetFullOWner(const std::string& tag);

  // Creates a node containing the province's history.
  std::shared_ptr<ParadoxNode> CreateHistoryNode() const;

private:
  int id;
  std::string name;
  std::string adjective;
  std::map<std::string, std::string> culturalNames;

  std::string ownerTag;
  std::string controllerTag;
  std::set<std::string> coreTags;

  std::string culture;
  std::string religion;
  bool hre;
  int baseTax;
  int baseProduction;
  int baseManpower;
  std::string capital;
  int extraCost;
  std::string tradeGood;

  std::set<std::string> discoveredByTechGroups;
  std::set<std::string> permanentModifiers;
};

} // EU4
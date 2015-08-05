#include "Mod.h"

#include <fstream>

#include <ParadoxNode\ParadoxNode.h>

#include "EU4\SupportedVersion.h"
#include "FileUtilities.h"

Mod::Mod(std::string modName, EU4::ProvinceCollection& provinces)
: modName(std::move(modName)),
  provinces(provinces)
{}

void Mod::WriteMod(const std::string& modsPath) const
{
  std::string modPath = modsPath + modName + '\\';
  std::string historyPath = modPath + "history\\";
  std::string provincesHistoryPath = historyPath + "provinces\\";

  FileUtilities::MakeFolder(modsPath);
  FileUtilities::MakeFolder(modPath);
  FileUtilities::MakeFolder(historyPath);
  FileUtilities::MakeFolder(provincesHistoryPath);

  WriteModFile(modsPath);
  provinces.WriteProvincesHistory(provincesHistoryPath);
}

void Mod::WriteModFile(const std::string& modsPath) const
{
  auto modRoot = ParadoxNode::CreateRoot();
  modRoot->AddChild(ParadoxNode::Create("name", "\"" + modName + "\""));
  modRoot->AddChild(ParadoxNode::Create("path", "\"mod/" + modName + "\""));
  modRoot->AddChild(ParadoxNode::Create("disable_time_widget", "yes"));
  modRoot->AddChild(ParadoxNode::Create("supported_version", EU4::supportedVersion));

  auto modFileName = modsPath + modName + ".mod";
  std::ofstream(modFileName) << modRoot;
}

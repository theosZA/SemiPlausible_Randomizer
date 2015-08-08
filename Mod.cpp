#include "Mod.h"

#include <fstream>

#include <ParadoxNode\ParadoxNode.h>

#include "EU4\SupportedVersion.h"
#include "FileUtilities.h"

Mod::Mod(std::string modName, const EU4::CountryCollection& countries, const EU4::ProvinceCollection& provinces)
: modName(std::move(modName)),
  countries(countries),
  provinces(provinces)
{}

void Mod::WriteMod(const std::string& modsPath) const
{
  std::string modPath = modsPath + modName + '\\';
  std::string commonPath = modPath + "common\\";
  std::string countryTagsPath = commonPath + "country_tags\\";
  std::string countriesCommonPath = commonPath + "countries\\";
  std::string historyPath = modPath + "history\\";
  std::string countriesHistoryPath = historyPath + "countries\\";
  std::string provincesHistoryPath = historyPath + "provinces\\";
  std::string localisationPath = modPath + "localisation\\";

  FileUtilities::MakeFolder(modsPath);
  FileUtilities::MakeFolder(modPath);
  FileUtilities::MakeFolder(commonPath);
  FileUtilities::MakeFolder(countryTagsPath);
  FileUtilities::MakeFolder(countriesCommonPath);
  FileUtilities::MakeFolder(historyPath);
  FileUtilities::MakeFolder(countriesHistoryPath);
  FileUtilities::MakeFolder(provincesHistoryPath);
  FileUtilities::MakeFolder(localisationPath);

  WriteModFile(modsPath);

  countries.WriteTags(countryTagsPath + "sp_r_countries.txt");
  countries.WriteCommonInfo(countriesCommonPath);
  countries.WriteHistory(countriesHistoryPath);
  countries.WriteLocalisation(localisationPath + "sp_r_countries_l_english.yml");

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

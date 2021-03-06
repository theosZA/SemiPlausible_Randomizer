#include "ProvinceCollection.h"

#include <fstream>
#include <stdexcept>

#include <ParadoxNode\ParadoxNode.h>

#include "Utility\SimpleYaml.h"
#include "Utility\StringUtilities.h"
#include "Utility\FileUtilities.h"

namespace EU4 {

ProvinceCollection::ProvinceCollection(const std::set<int>& provinceIDs,
                                       const std::string& provincesHistoryPath,
                                       const std::string& provincesNamesPath,
                                       const std::string& localisationPath)
{
  auto provinceNames = SimpleYaml::ParseYamlFile(localisationPath + "prov_names_l_english.yml");
  auto provinceAdjectives = SimpleYaml::ParseYamlFile(localisationPath + "prov_names_adj_l_english.yml");

  std::map<int, std::map<std::string, std::string>> cultureProvinceNames;
  auto provinceNamesFileNames = FileUtilities::GetAllFilesInFolder(provincesNamesPath);
  for (const auto& provinceNamesFileName : provinceNamesFileNames)
  {
    auto culture = provinceNamesFileName.substr(0, provinceNamesFileName.find('.'));
    auto provinceNamesNode = ParadoxNode::ParseFromFile(provincesNamesPath + provinceNamesFileName);
    for (const auto& provinceNameNode : provinceNamesNode->GetChildren())
    {
      auto provinceID = std::stoi(provinceNameNode->GetKey());
      const auto& cultureProvinceName = provinceNameNode->GetValue();
      cultureProvinceNames[provinceID].emplace(culture, cultureProvinceName);
    }
  }

  auto provinceFileNames = FileUtilities::GetAllFilesInFolder(provincesHistoryPath);
  for (const auto& provinceFileName : provinceFileNames)
  {
    int provinceID = std::stoi(provinceFileName);
    if (provinceIDs.find(provinceID) != provinceIDs.end())
    {
      auto splitPos = provinceFileName.find('-');
      auto extPos = provinceFileName.rfind('.');
      if (splitPos != std::string::npos && extPos != std::string::npos)
      {
        auto provinceName = provinceNames["PROV" + std::to_string(provinceID)];
        auto provinceAdjective = provinceAdjectives["PROV_ADJ" + std::to_string(provinceID)];
        auto provinceFullPath = provincesHistoryPath + provinceFileName;
        Province province(provinceID, provinceName, provinceAdjective, cultureProvinceNames[provinceID], *ParadoxNode::ParseFromFile(provinceFullPath));
        provinces.emplace(provinceID, std::move(province));
        provinceHistoryFileNames[provinceID] = provinceFileName;
      }
    }
  }
}

const Province & ProvinceCollection::GetProvince(int provinceID) const
{
  auto findIter = provinces.find(provinceID);
  if (findIter == provinces.end())
    throw std::runtime_error("Province " + std::to_string(provinceID) + " not found");
  return findIter->second;
}

Province & ProvinceCollection::GetProvince(int provinceID)
{
  auto findIter = provinces.find(provinceID);
  if (findIter == provinces.end())
    throw std::runtime_error("Province " + std::to_string(provinceID) + " not found");
  return findIter->second;
}

void ProvinceCollection::ClearTags()
{
  for (auto& province : provinces)
    province.second.ClearTags();
}

void ProvinceCollection::WriteProvincesHistory(const std::string& provincesHistoryPath) const
{
  for (const auto& province : provinces)
  {
    auto fileNameFindIter = provinceHistoryFileNames.find(province.first);
    if (fileNameFindIter != provinceHistoryFileNames.end())
    {
      auto fileName = provincesHistoryPath + fileNameFindIter->second;
      std::ofstream provinceFile(fileName);
      provinceFile << province.second.CreateHistoryNode();
    }
  }
}

} // EU4
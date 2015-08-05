#include "ProvinceCollection.h"

#include <fstream>
#include <stdexcept>

#include <ParadoxNode\ParadoxNode.h>

#include "FileUtilities.h"
#include "StringUtilities.h"

namespace EU4 {

ProvinceCollection::ProvinceCollection(const std::set<int>& provinceIDs, const std::string & provincesHistoryPath)
{
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
        auto provinceName = TrimWhitespace(provinceFileName.substr(splitPos + 1, extPos - (splitPos + 1)));
        auto provinceFullPath = provincesHistoryPath + provinceFileName;
        Province province(provinceID, provinceName, *ParadoxNode::ParseFromFile(provinceFullPath));
        provinces.emplace(provinceID, std::move(province));
        provinceHistoryFileNames[provinceID] = provinceFileName;
      }
    }
  }
}

void ProvinceCollection::ClearTags()
{
  for (auto& province : provinces)
    province.second.ClearTags();
}

void ProvinceCollection::SetFullOWner(int provinceID, const std::string& tag)
{
  auto findIter = provinces.find(provinceID);
  if (findIter == provinces.end())
    throw std::runtime_error("Province " + std::to_string(provinceID) + " no found");
  findIter->second.SetFullOWner(tag);
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
#pragma once

#include <string>
#include <vector>

class ParadoxNode;

class Config
{
public:
  Config(const ParadoxNode&);

  const std::string& GetModName() const { return modName; }
  const std::string& GetEU4Path() const { return eu4Path; }
  const std::vector<std::string>& GetRegionsToGenerate() const { return generateRegions; }
  const std::vector<int>& GetProvincesToGenerate() const { return generateProvinces; }

private:
  std::string modName;
  std::string eu4Path;
  std::vector<std::string> generateRegions;
  std::vector<int> generateProvinces;
};
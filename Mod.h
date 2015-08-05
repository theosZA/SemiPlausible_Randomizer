#pragma once

#include <string>

#include "EU4\ProvinceCollection.h"

// Holds all the details you need to write a mod package - mod file plus mod folder.
class Mod
{
public:
  Mod(std::string modName, EU4::ProvinceCollection& provinces);

  void WriteMod(const std::string& modsPath) const;

private:
  void WriteModFile(const std::string& modsPath) const;

  std::string modName;
  EU4::ProvinceCollection& provinces;
};
#pragma once

#include <map>
#include <string>

#include "EU4\Country.h"

namespace EU4 {

// Holds all the countries to be included in the EU4 mod.
class CountryCollection
{
  public:
    CountryCollection();

    // Adds a new country based on the given province. Returns the new country's tag.
    std::string AddNewCountry(const Province&, std::string religion, std::string primaryCulture);

    // Writes all countries' tags.
    void WriteTags(const std::string& fileName) const;
    // Writes all countries' common information such as colour.
    void WriteCommonInfo(const std::string& path) const;
    // Writes all countries' history including current situation such as current government and religion.
    void WriteHistory(const std::string& path) const;
    // Writes all countries' name and adjective for localisation.
    void WriteLocalisation(const std::string& fileName) const;
    // Writes all countries' flags to files in TGA format.
    void WriteFlags(const std::string& path) const;

  private:
    std::string PickNextTag();

    std::map<std::string, Country> countries;
    std::string nextTag;
};

} // EU4
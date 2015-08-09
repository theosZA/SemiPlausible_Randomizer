#include "CountryCollection.h"

#include <fstream>
#include <stdexcept>

#include <ParadoxNode\ParadoxNode.h>

namespace EU4 {

// Strip out all characters that aren't just standard letters (A-Z,a-z).
std::string NormalizeName(const std::string& name)
{
  std::string normalized;
  for (char c : name)
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
      normalized.push_back(c);
  return normalized;
}

CountryCollection::CountryCollection()
: nextTag("G01")
{}

std::string CountryCollection::AddNewCountry(const Province& province, std::string religion, std::string primaryCulture)
{
  auto tag = PickNextTag();
  countries.emplace(tag, Country(tag, province, religion, primaryCulture));
  return tag;
}

void CountryCollection::WriteTags(const std::string& fileName) const
{
  auto tagsNode = ParadoxNode::CreateRoot();
  for (const auto& countryPair : countries)
    tagsNode->AddChild(ParadoxNode::Create(countryPair.first, "countries/" + NormalizeName(countryPair.second.GetName()) + ".txt"));
  tagsNode->WriteToFile(fileName);
}

void CountryCollection::WriteCommonInfo(const std::string& path) const
{
  for (const auto& countryPair : countries)
  {
    const auto& country = countryPair.second;
    country.CreateCommonNode()->WriteToFile(path + NormalizeName(country.GetName()) + ".txt");
  }
}

void CountryCollection::WriteHistory(const std::string& path) const
{
  for (const auto& countryPair : countries)
  {
    const auto& country = countryPair.second;
    country.CreateHistoryNode()->WriteToFile(path + country.GetTag() + " - " + NormalizeName(country.GetName()) + ".txt");
  }
}

void CountryCollection::WriteLocalisation(const std::string& fileName) const
{
  std::ofstream localisationCountriesFile(fileName);
  if (!localisationCountriesFile)
    throw std::runtime_error("Error creating countries localistion file");
  localisationCountriesFile << char(0xEF) << char(0xBB) << char(0xBF) // UTF-8 BOM required by EU4
                            << "l_english:\n";
  for (const auto& countryPair : countries)
  {
    const auto& country = countryPair.second;
    localisationCountriesFile << ' ' << country.GetTag() << ": \"" << country.GetName() << "\"\n"
                              << ' ' << country.GetTag() << "_ADJ: \"" << country.GetAdjective() << "\"\n";
  }
}

void CountryCollection::WriteFlags(const std::string& path) const
{
  for (const auto& countryPair : countries)
  {
    const auto& country = countryPair.second;
    country.WriteFlagFile(path + country.GetTag() + ".tga");
  }
}

std::string CountryCollection::PickNextTag()
{
  auto tag = nextTag;
  // Increase next tag.
  ++nextTag[2];
  if (nextTag[2] > '9')
  {
    nextTag[2] = '0';
    ++nextTag[1];
    if (nextTag[1] > '9')
    {
      ++nextTag[0];
      if (nextTag[0] > 'Z')
        throw std::runtime_error("Insufficient tags available");
    }
  }
  return tag;
}

} // EU4
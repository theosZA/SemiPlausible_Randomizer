#include "SimpleYaml.h"

#include <fstream>

namespace SimpleYaml {

std::map<std::string, std::string> ParseYaml(std::istream& in)
{
  std::map<std::string, std::string> items;
  std::string header;
  std::getline(in, header);
  while (in && !in.eof())
  {
    std::string currentLine;
    std::getline(in, currentLine);

    auto keyPos = currentLine.find_first_not_of(' ');
    auto colonPos = currentLine.find(':', keyPos + 1);
    auto startQuotePos = currentLine.find('"', colonPos + 1);
    auto endQuotePos = currentLine.find('"', startQuotePos + 1);

    auto key = currentLine.substr(keyPos, colonPos - keyPos);
    auto value = currentLine.substr(startQuotePos + 1, endQuotePos - startQuotePos - 1);
    items.emplace(key, value);
  }
  return items;
}

std::map<std::string, std::string> ParseYamlFile(const std::string& fileName)
{
  std::ifstream inputFile(fileName);
  return ParseYaml(inputFile);
}

} // namespace Yaml
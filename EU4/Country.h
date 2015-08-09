#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "Image.h"

class ParadoxNode;

namespace EU4 {

class Province;

// A country (corresponds to a tag) in EU4.
class Country
{
public:
  // Constructor for a new country based on a given province.
  Country(std::string tag, const Province&, std::string religion, std::string primaryCulture);

  // Returns this country's tag.
  const std::string& GetTag() const { return tag; }
  // Returns the contry's name.
  const std::string& GetName() const { return name; }
  // Returns the adjective to describe the country.
  const std::string& GetAdjective() const { return adjective; }

  // Returns a node with the country's common information such as colour.
  std::shared_ptr<ParadoxNode> CreateCommonNode() const;
  // Returns a node with the country's history including current situation such as current government and religion.
  std::shared_ptr<ParadoxNode> CreateHistoryNode() const;
  // Writes this country's flag to file in TGA format.
  void WriteFlagFile(const std::string& fileName) const;

private:
  std::string tag;
  std::string name;
  std::string adjective;
  Image<128, 128> flag;

  // Common
  std::string graphicalCulture;
  std::vector<int> colour;

  // History
  std::string government;
  std::string techGroup;
  std::string religion;
  std::string primaryCulture;
  int capitalProvince;
};

} // namespace EU4
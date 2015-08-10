#pragma once

#include <iosfwd>
#include <map>
#include <string>

namespace SimpleYaml {

std::map<std::string, std::string> ParseYaml(std::istream&);
std::map<std::string, std::string> ParseYamlFile(const std::string& fileName);

} // namespace SimpleYaml
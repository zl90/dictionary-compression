#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace json
{
    std::vector<std::string> parse(std::string);

    void encode(const std::unordered_map<std::string, std::string> &, std::string, std::string);
}
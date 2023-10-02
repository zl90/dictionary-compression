#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace dict_compression
{
    std::unordered_map<std::string, int> map_token_frequencies(std::vector<std::string>);
}

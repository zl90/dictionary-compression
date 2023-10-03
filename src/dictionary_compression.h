#pragma once

#include <vector>
#include <string>
#include <unordered_map>

namespace dict_compression
{
    std::unordered_map<std::string, int> map_token_frequencies(const std::vector<std::string> &);

    std::unordered_map<std::string, std::string> build_dictionary(const std::unordered_map<std::string, int> &);
}

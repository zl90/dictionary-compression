#include "dictionary_compression.h"
#include <functional>
#include <cmath>
#include <sstream>

std::unordered_map<std::string, int> dict_compression::map_token_frequencies(const std::vector<std::string> &tokens)
{
    std::unordered_map<std::string, int> output;

    for (int i = 0; i < tokens.size(); i++)
    {
        auto existing_key = output.find(tokens[i]);

        if (existing_key != output.end())
        {
            output[tokens[i]] = output[tokens[i]] + 1;
        }
        else
        {
            output.insert({tokens[i], 1});
        }
    }

    return output;
}

std::unordered_map<std::string, std::string> dict_compression::build_dictionary(const std::unordered_map<std::string, int> &input)
{
    std::unordered_map<std::string, std::string> output;

    long count = 0;
    char delimiter = 0b00011110; // ascii record separator

    for (const auto &pair : input)
    {
        const std::string &key = pair.first;
        const int value = pair.second;

        std::stringstream stream;
        stream << std::hex << count;
        const std::string hexCount(stream.str());

        const std::string hashString = delimiter + hexCount;

        if (value > 1 && key.length() > hashString.length())
        {
            output.insert({key, hashString});

            count++;
        }
    }

    return output;
}

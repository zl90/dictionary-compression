#include "dictionary_compression.h"
#include <functional>
#include <cmath>

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

    const u_short MIN_TOKEN_LENGTH = 7; // We can't encode tokens that are smaller than our hash length because we wouldn't be saving space

    for (const auto &pair : input)
    {
        const std::string &key = pair.first;
        const int value = pair.second;
        if ((value > 1 && key.length() >= MIN_TOKEN_LENGTH))
        {
            const std::size_t hash = std::hash<std::string>{}(key) % static_cast<int>(std::pow(10.0, static_cast<double>(MIN_TOKEN_LENGTH)));

            const std::string hashString = std::to_string(hash);

            output.insert({key, hashString});
        }
    }

    return output;
}

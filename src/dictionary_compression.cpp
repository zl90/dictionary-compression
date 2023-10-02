#include "dictionary_compression.h"

std::unordered_map<std::string, int> dict_compression::map_token_frequencies(std::vector<std::string> tokens)
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
#include "json.h"
#include "dictionary_compression.h"
#include <iostream>
#include <unordered_map>

#define INPUT_FILENAME "input.json"

int main()
{
    try
    {
        std::vector<std::string> tokens;
        tokens = json::parse(INPUT_FILENAME);

        std::unordered_map<std::string, int> frequencies = dict_compression::map_token_frequencies(tokens);

        std::unordered_map<std::string, std::string> dictionary = dict_compression::build_dictionary(frequencies);

        for (const auto &pair : dictionary)
        {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }

        std::cout << dictionary.size() << std::endl;

        return 0;
    }
    catch (...)
    {
        return -1;
    }
}
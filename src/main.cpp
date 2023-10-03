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

        for (const auto &pair : frequencies)
        {
            if (pair.second > 10)
            {
                std::cout << pair.first << ": " << pair.second << std::endl;
            }
        }

        std::cout << frequencies.size() << std::endl;

        return 0;
    }
    catch (...)
    {
        return -1;
    }
}
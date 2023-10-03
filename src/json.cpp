#include <fstream>
#include <stdexcept>
#include <iostream>
#include "json.h"

std::vector<std::string> json::parse(std::string path)
{
    try
    {
        std::ifstream file(path);
        std::vector<std::string> output;

        if (!file.is_open())
        {
            throw std::invalid_argument("Incorrect File Path");
        }

        char next_char;
        bool in_word = false;
        std::string next_word = "";

        while (file.get(next_char))
        {
            if (!in_word && next_char == '"')
            {
                in_word = true;
            }
            else if (in_word && next_char == '"')
            {
                in_word = false;

                if (next_word.size() > 0)
                {
                    output.push_back(next_word);
                }

                next_word = "";
            }
            else if (in_word)
            {
                next_word += next_char;
            }
        }

        file.close();
        return output;
    }
    catch (std::invalid_argument &error)
    {
        std::cerr << "json_lexer::parse(): " << error.what() << std::endl;
        std::vector<std::string> empty;
        return empty;
    }
}
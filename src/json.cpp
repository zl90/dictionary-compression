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

        bool erroneous = false;
        bool erroneous_prev = false;

        bool in_escape = false;

        while (file.get(next_char))
        {
            if (!in_word && next_char == '"')
            {
                in_word = true;
            }
            else if (in_word)
            {
                if (in_escape)
                {
                    // Handle escape sequences
                    in_escape = false;
                    if (next_char == 'n')
                    {
                        next_word += '\n';
                    }
                    else if (next_char == 't')
                    {
                        next_word += '\t';
                    }
                    else if (next_char == '"')
                    {
                        next_word += '"';
                    }
                    else if (next_char == '\\')
                    {
                        next_word += '\\';
                    }
                }
                else if (next_char == '\\')
                {
                    // Start of an escape sequence
                    in_escape = true;
                }
                else if (next_char == '"')
                {
                    in_word = false;
                    output.push_back(next_word);
                    next_word = "";
                }
                else
                {
                    next_word += next_char;
                }
            }
        }

        file.close();
        return output;
    }
    catch (std::invalid_argument &error)
    {
        std::cerr << "json::parse(): " << error.what() << std::endl;
        std::vector<std::string> empty;
        return empty;
    }
}

void json::encode(const std::unordered_map<std::string, std::string> &dictionary, std::string input_path, std::string output_path)
{
    try
    {
        std::ifstream input(input_path);
        std::ofstream output(output_path);

        if (!input.is_open())
        {
            throw std::invalid_argument("Incorrect Input File Path");
            return;
        }

        if (!output.is_open())
        {
            throw std::invalid_argument("Incorrect Output File Path");
            return;
        }

        char next_char;
        bool in_word = false;
        std::string next_word = "";

        while (input.get(next_char))
        {
            if (!in_word && next_char == '"')
            {
                in_word = true;
            }
            else if (in_word)
            {
                if (next_char == '\\')
                {
                    // Handle escape sequences
                    next_word += next_char; // Add the backslash

                    if (input.get(next_char))
                    {
                        next_word += next_char; // Add the escaped character
                    }
                    else
                    {
                        // Handle unexpected end of input
                        break;
                    }
                }
                else if (next_char == '"')
                {
                    in_word = false;

                    if (!next_word.empty())
                    {
                        auto existing_key = dictionary.find(next_word);

                        if (existing_key != dictionary.end())
                        {
                            // Hashable word found, write the hash
                            std::string hash = existing_key->second;
                            output << '"' << hash << '"';
                        }
                        else
                        {
                            // Non-hashable word, write the original word
                            output << '"' << next_word << '"';
                        }
                    }
                    else
                    {
                        output << "\"\"";
                    }

                    next_word = "";
                }
                else
                {
                    next_word += next_char;
                }
            }
            else
            {
                output << next_char;
            }
        }

        // Append the dictionary to the file as CSV
        const char dictionary_delimiter = 0b00011111; // ascii unit separator
        output << dictionary_delimiter;
        for (auto i = dictionary.begin(); i != dictionary.end(); i++)
        {
            const std::string key = i->first;
            const std::string hash = i->second;

            output << '"' + key + '"' + ',' + '"' + hash + '"' + '\n';
        }

        output.close();
        input.close();
    }
    catch (std::invalid_argument &error)
    {
        std::cerr << "json::encode(): " << error.what() << std::endl;
        return;
    }
}

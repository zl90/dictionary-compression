#include "json_lexer.h"
#include <iostream>

int main()
{
    try
    {
        std::vector<std::string> tokens;
        tokens = json_lexer::parse("input.json");

        for (int i = 0; i < 100; i++)
        {
            std::cout << tokens[i] << std::endl;
        }

        std::cout << tokens.size() << std::endl;

        return 0;
    }
    catch (...)
    {
        return -1;
    }
}
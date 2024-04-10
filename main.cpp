#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "DataRecorder.hpp"

int main()
{
    std::string input;

    DataRecorder rec;

    while (true)
    {
        std::getline(std::cin, input);

        if (input == "exit")
            return 0;

        if (input.find('?') != std::string::npos)
        {
            if (input.find('"') != std::string::npos)
            {
                rec.Save(input);
                continue;
            }

            rec.Print(input);
        }
        else
        {
            std::cout << "Unknown input" << std::endl;
        }
    }

    return 0;
}
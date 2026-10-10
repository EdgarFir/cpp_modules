#include <iostream>
#include "FileReader/include/FileReader.hpp"

int main()
{
    FileReader file_reader;

    if (!file_reader.ReadFile("data.csv"))
    {
        std::cout << "Error reading file.";
        return 1;
    }

    const auto& file_lines = file_reader.GetFileLines();

    std::cout << "Number of lines read: " 
              << file_lines.size()
              << std::endl;

    return 0;
}
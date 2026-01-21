#include <iostream>

/**
 * @brief Convert string to uppercase.
 * 
 * @param str String to convert.
 * 
 * @return String converterd to uppercase.
 */
std::string to_uppercase(std::string str) 
{
    std::string upper_str = str;

    for (size_t i = 0; i < str.size(); i++)
        upper_str[i] = std::toupper(upper_str[i]);
    return upper_str;
}

int main (int argc, char **argv) {
    
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
            std::cout << to_uppercase(argv[i]);
        std::cout << std::endl;
    }
    else
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    return 0;
}
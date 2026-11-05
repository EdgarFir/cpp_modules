#ifndef BITCOINEXCHANGEFILEREADER_HPP
#define BITCOINEXCHANGEFILEREADER_HPP

#include <string>
#include <cctype>
#include <fstream>


class BitcoinExchangeFileReader
{
    public:
        enum FileReadResult
        {
            SUCCESS,
            END_OF_FILE,
            ERROR_READING,
            ERROR_DELIMITER_NOT_FOUND
        };

        struct Config
        {
            std::string filename;
            char separator;
            bool required_spaces_around_separator;
        };

        BitcoinExchangeFileReader(const std::string& filename, const char key_value_separator);
        ~BitcoinExchangeFileReader();

        FileReadResult ReadNext(std::string& date, std::string& value);
        
        
    private:
        BitcoinExchangeFileReader();
        BitcoinExchangeFileReader(const BitcoinExchangeFileReader& other);
        BitcoinExchangeFileReader& operator=(const BitcoinExchangeFileReader& other);

        FileReadResult ReadLine(std::string& line);
        FileReadResult ParseLineValuesFromDelimiter(const std::string& line,
                                                    std::string& val1,
                                                    std::string& val2);

        std::ifstream file_;
        char delimiter_;
};

#endif

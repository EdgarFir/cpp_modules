#include "../include/BitcoinExchangeFileReader.hpp"

BitcoinExchangeFileReader::BitcoinExchangeFileReader(const std::string& filename, const char key_value_separator) 
    : file_(filename.c_str()), 
        delimiter_(key_value_separator)
{
    if (!file_.is_open())
    {
        throw std::runtime_error("Error opening file");
    }
}

BitcoinExchangeFileReader::~BitcoinExchangeFileReader()
{
}

BitcoinExchangeFileReader::FileReadResult BitcoinExchangeFileReader::ReadNext(std::string& date, std::string& value)
{
    std::string line;
    FileReadResult res = ReadLine(line);  
    if (res != SUCCESS)
    {
        return res;
    }

    return ParseLineValuesFromDelimiter(line, date, value);
}

BitcoinExchangeFileReader::FileReadResult BitcoinExchangeFileReader::ReadLine(std::string& line)
{
    if (std::getline(file_, line))
    {
        return SUCCESS;
    }

    if (file_.eof())
    {
        return END_OF_FILE;
    }

    return ERROR_READING;
}

BitcoinExchangeFileReader::FileReadResult BitcoinExchangeFileReader::ParseLineValuesFromDelimiter(const std::string& line,
                                                                                                 std::string& val1,
                                                                                                 std::string& val2)
{
    const size_t line_begin = 0;
    const size_t separator_pos = line.find(delimiter_, line_begin);
    if (separator_pos == std::string::npos)
    {
        return ERROR_DELIMITER_NOT_FOUND;
    }
    val1 = line.substr(0, separator_pos);
    val2 = line.substr(separator_pos + 1);
    
    return SUCCESS;
}

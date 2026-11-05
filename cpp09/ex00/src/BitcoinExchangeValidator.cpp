#include "../include/BitcoinExchangeValidator.hpp"
#include <errno.h>

BitcoinExchangeValidator::BitcoinExchangeValidator(const Config& config) : config_(config)
{
}

BitcoinExchangeValidator::~BitcoinExchangeValidator()
{
}

BitcoinExchangeValidator::ValidationResult BitcoinExchangeValidator::ValidateHeaders(const std::string& key_header, const std::string& value_header)
{
    if (config_.date_header == key_header &&
        config_.value_header == value_header)
    {
        return SUCCESS;
    }

    return ERROR_MISMATCH_EXPECTED_HEADERS;
}

BitcoinExchangeValidator::ValidationResult BitcoinExchangeValidator::ValidateDate(const std::string& date)
{
    const size_t expected_date_size = 10;
    if (date.size() != expected_date_size)
    {
        return ERROR_DATE_BAD_FORMAT;
    }

    const char expected_separator = '-';
    const size_t expected_first_separator_pos = 4;
    if (date[expected_first_separator_pos] != expected_separator)
    {
        return ERROR_DATE_BAD_FORMAT;
    }

    const size_t expected_sec_separator_pos = 7;
    if (date[expected_sec_separator_pos] != expected_separator)
    {
        return ERROR_DATE_BAD_FORMAT;
    }

    // Validate year
    const std::string year_str = date.substr(0, expected_first_separator_pos);
    float year = 0;
    if (!HasOnlyDigits(year_str) || ConverStringToFloat(year_str, year) != SUCCESS)
    {
        return ERROR_DATE_BAD_YEAR;
    }

    // Validate month
    const size_t month_input_size = 2; 
    const std::string month_str = date.substr(expected_first_separator_pos + 1, month_input_size);
    float month = 0;
    if (!HasOnlyDigits(month_str) || ConverStringToFloat(month_str, month) != SUCCESS)
    {
        return ERROR_DATE_BAD_MONTH;
    }

    // Validate day
    const std::string day_str = date.substr(expected_sec_separator_pos + 1);
    float day = 0;
    if (!HasOnlyDigits(day_str) || ConverStringToFloat(day_str, day) != SUCCESS)
    {
        return ERROR_DATE_BAD_DAY;
    }

    // Check date bounds
    if (year < 2009 || (month < 1 || month > 12) || (day < 1 || day > GetMonthMaxDays(static_cast<int>(year), static_cast<int>(month))))
    {
        return ERROR_DATE_BAD_FORMAT;
    }

    return SUCCESS;
}

BitcoinExchangeValidator::ValidationResult BitcoinExchangeValidator::ValidateAndConvertFloatInput(const std::string& value_in, float& value_out)
{
    ValidationResult res = ConverStringToFloat(value_in, value_out);
    if (res != SUCCESS)
    {
        return res;
    }

    if (value_out < 0)
    {
        return ERROR_VALUE_NEGATIVE;
    }

    if (config_.max_limit > 0 && value_out > config_.max_limit)
    {
        return ERROR_VALUE_HIGHER_THAN_MAX_LIMIT;
    }

    return SUCCESS;
}

BitcoinExchangeValidator::ValidationResult BitcoinExchangeValidator::ValidateInputFormat(const std::string& date, const std::string& value)
{
    if ((!date.empty() && date[date.size() - 1] != ' ') || (!value.empty() && value[0] != ' '))
    {
        return ERROR_BAD_INPUT_FORMAT;
    }

    return SUCCESS;
}

bool BitcoinExchangeValidator::HasOnlyDigits(const std::string& str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(str[i])))
        {
            return false;
        }
    }
    return true;
}

int BitcoinExchangeValidator::GetMonthMaxDays(const int year, const int month)
{
    int max_days = 0;

    if (month == 2)
    {
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
        {
            max_days = 29;
        }
        else
        {
            max_days = 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        max_days = 30;
    }
    else
    {
        max_days = 31;
    }

    return max_days;
}

BitcoinExchangeValidator::ValidationResult BitcoinExchangeValidator::ConverStringToFloat(const std::string& str, float& value)
{        
    char* end_ptr = NULL;
    errno = 0;
    double result = std::strtod(str.c_str(), &end_ptr);
    if (end_ptr == str.c_str() || *end_ptr != '\0')
    {
        return ERROR_VALUE_BAD_NUMBER;
    }
    if (errno == ERANGE || result > std::numeric_limits<float>::max() ||
        result < -std::numeric_limits<float>::max())
    {   
        return ERROR_VALUE_OVERFLOW;
    }    
    value = static_cast<float>(result);
    
    return SUCCESS;
}

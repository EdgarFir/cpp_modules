#ifndef BITCOINEXCHANGEVALIDATOR_HPP
#define BITCOINEXCHANGEVALIDATOR_HPP

#include <limits>
#include <cstdlib>
#include <cctype>
#include <string>

class BitcoinExchangeValidator
{
    public: 
        enum ValidationResult
        {
            SUCCESS,
            ERROR_MISMATCH_EXPECTED_HEADERS,
            ERROR_DATE_BAD_FORMAT,
            ERROR_DATE_BAD_YEAR,
            ERROR_DATE_BAD_MONTH,
            ERROR_DATE_BAD_DAY,
            ERROR_VALUE_BAD_NUMBER,
            ERROR_VALUE_OVERFLOW,
            ERROR_VALUE_NEGATIVE,
            ERROR_VALUE_HIGHER_THAN_MAX_LIMIT,
            ERROR_BAD_INPUT_FORMAT,
            ERROR_DELIMITER_NOT_FOUND
        };

        struct Config
        {
            std::string date_header;
            std::string value_header;
            float max_limit;
        };

        BitcoinExchangeValidator(const Config& config);
        ~BitcoinExchangeValidator();
        BitcoinExchangeValidator(const BitcoinExchangeValidator& other);
        BitcoinExchangeValidator& operator=(const BitcoinExchangeValidator& other);

        ValidationResult ValidateHeaders(const std::string& key_header, const std::string& value_header);
        ValidationResult ValidateDate(const std::string& date);
        ValidationResult ValidateAndConvertFloatInput(const std::string& value_in, float& value_out);
        ValidationResult ValidateInputFormat(const std::string& date, const std::string& value);

    private:
        bool HasOnlyDigits(const std::string& str);
        int GetMonthMaxDays(const int year, const int month);
        ValidationResult ConverStringToFloat(const std::string& str, float& value);
            
        Config config_;
};

#endif

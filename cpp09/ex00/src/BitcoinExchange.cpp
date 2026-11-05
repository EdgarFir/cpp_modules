
#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : bitcoin_db_()
{
    std::cout << "BitcoinExchange default ctor called\n";
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << "BitcoinExchange dtor called\n";
}

bool BitcoinExchange::LoadCsvDatabase(const std::string& csv_filename)
{
    BitcoinExchangeValidator::Config validation_config;
    validation_config.date_header = "date";
    validation_config.value_header = "exchange_rate";
    validation_config.max_limit = 0;

    BitcoinExchangeFileReader::Config file_config;
    file_config.filename = csv_filename;
    file_config.separator = ',';
    file_config.required_spaces_around_separator = false;

    if (!ProcessFile(file_config, validation_config, &BitcoinExchange::CsvDatabaseProcessCallback))
    {
    if (!bitcoin_db_.empty())
    {
        bitcoin_db_.clear();
    }
    return false;
    }

    if (bitcoin_db_.empty())
    {
    std::cout << "Error: CSV database is empty\n";
    return false;
    }
    std::cout << "Bitcoin exchange database loaded with success\n";

    return true;
}

bool BitcoinExchange::LoadInputAndDisplayResults(const std::string& input_filename)
{
    BitcoinExchangeFileReader::Config file_config;
    file_config.filename = input_filename;
    file_config.separator = '|';
    file_config.required_spaces_around_separator = true;

    BitcoinExchangeValidator::Config validation_config;
    validation_config.date_header = "date";
    validation_config.value_header = "value";
    validation_config.max_limit = 1000;

    if (!ProcessFile(file_config, validation_config, &BitcoinExchange::InputProcessCallback))
    {
        return false;
    }

    return true;
}

bool BitcoinExchange::CsvDatabaseProcessCallback(const BitcoinExchangeValidator::ValidationResult& validation_res, 
                                const std::string& date, 
                                const float exchange_rate)
{
    if (validation_res != BitcoinExchangeValidator::SUCCESS)
    {
        PrintErrorMessage(validation_res, date);
        return false;
    }

    if (bitcoin_db_.find(date) != bitcoin_db_.end())
    {
        std::cout << "Error: Duplicate date in database: " << date << '\n';
        return false;
    }
    bitcoin_db_[date] = exchange_rate;

    return true;
}

bool BitcoinExchange::InputProcessCallback(const BitcoinExchangeValidator::ValidationResult& validation_res,
                            const std::string& date,
                            const float value)
{
    if (validation_res != BitcoinExchangeValidator::SUCCESS)
    {
        PrintErrorMessage(validation_res, date);
        return true;
    }

    std::map<std::string, float>::const_iterator it = bitcoin_db_.upper_bound(date);
    if (it == bitcoin_db_.begin())
    {
        std::cout << "Error: No exchange rate available for this date.\n";
        return true;
    }
    --it;

    const double result = static_cast<double>(value) * static_cast<double>(it->second);
    std::cout << date << " => " << value << " = " << result << '\n';

    return true;
}

std::string BitcoinExchange::CleanStringWhiteSpaces(const std::string& str)
{
    std::string::const_iterator begin_it = str.begin();
    std::string::const_iterator end_it = str.end();

    std::string result;
    while (begin_it != end_it && std::isspace(static_cast<unsigned char>(*begin_it)))
    {
        ++begin_it;
    }
    if (begin_it == end_it)
    {
        return result;
    }
    while (std::isspace(static_cast<unsigned char>(*(end_it - 1))))
    {
        --end_it;
    }
    result = std::string(begin_it, end_it);
    return result;
}

void BitcoinExchange::PrintErrorMessage(const BitcoinExchangeValidator::ValidationResult& result,
                        const std::string& value)
{
    switch (result)
    {
        case BitcoinExchangeValidator::ERROR_MISMATCH_EXPECTED_HEADERS:
            std::cout << "Error: invalid file header.\n";
            break;

        case BitcoinExchangeValidator::ERROR_DATE_BAD_FORMAT:
        case BitcoinExchangeValidator::ERROR_DATE_BAD_YEAR:
        case BitcoinExchangeValidator::ERROR_DATE_BAD_MONTH:
        case BitcoinExchangeValidator::ERROR_DATE_BAD_DAY:
            std::cout << "Error: bad input => " << value << '\n';
            break;

        case BitcoinExchangeValidator::ERROR_VALUE_BAD_NUMBER:
            std::cout << "Error: invalid number.\n";
            break;

        case BitcoinExchangeValidator::ERROR_VALUE_OVERFLOW:
            std::cout << "Error: too large a number.\n";
            break;

        case BitcoinExchangeValidator::ERROR_VALUE_NEGATIVE:
            std::cout << "Error: not a positive number.\n";
            break;

        case BitcoinExchangeValidator::ERROR_VALUE_HIGHER_THAN_MAX_LIMIT:
            std::cout << "Error: too large a number.\n";
            break;

        case BitcoinExchangeValidator::ERROR_BAD_INPUT_FORMAT:
            std::cout << "Error: bad input => " << value << '\n';
            break;
        case BitcoinExchangeValidator::ERROR_DELIMITER_NOT_FOUND:
            std::cout << "Error: Bad input format: missing delimiter.\n";
            break;
        case BitcoinExchangeValidator::SUCCESS:
            break;
    }
}
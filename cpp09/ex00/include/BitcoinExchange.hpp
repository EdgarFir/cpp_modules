#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "BitcoinExchangeFileReader.hpp"
#include "BitcoinExchangeValidator.hpp"

class BitcoinExchange
{
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        
        bool LoadCsvDatabase(const std::string& csv_filename);
        bool LoadInputAndDisplayResults(const std::string& input_filename);
    
        private:
        bool CsvDatabaseProcessCallback(const BitcoinExchangeValidator::ValidationResult& validation_res, 
            const std::string& date, 
            const float exchange_rate);
            
        bool InputProcessCallback(const BitcoinExchangeValidator::ValidationResult& validation_res,
            const std::string& date,
            const float value);
            
        std::string CleanStringWhiteSpaces(const std::string& str);
    
        void PrintErrorMessage(const BitcoinExchangeValidator::ValidationResult& result,
                                const std::string& value = "");

        template <typename Callback>
        bool ProcessFile(const BitcoinExchangeFileReader::Config& file_config,
                            const BitcoinExchangeValidator::Config& bitcoin_validator_config,
                            Callback callback)
        {
            try
            {
                BitcoinExchangeValidator file_content_validator(bitcoin_validator_config);  
                BitcoinExchangeFileReader file_reader(file_config.filename, file_config.separator);
                
                bool header_is_validated = false;
                std::string first_delimited_val;
                std::string sec_delimited_val;
                while (true)
                {
                    BitcoinExchangeFileReader::FileReadResult read_res = file_reader.ReadNext(first_delimited_val, sec_delimited_val);
                    if (read_res == BitcoinExchangeFileReader::END_OF_FILE)
                        break;

                    if (read_res == BitcoinExchangeFileReader::ERROR_READING)
                    {
                        std::cout << "Error: Failed to read file '" << file_config.filename << "'.\n";
                        return false;
                    }

                    if (read_res == BitcoinExchangeFileReader::ERROR_DELIMITER_NOT_FOUND)
                    {
                        if (!(this->*callback)(BitcoinExchangeValidator::ERROR_DELIMITER_NOT_FOUND, "", 0))
                        {
                            return false;
                        }
                        continue;
                    }

                    if (file_config.required_spaces_around_separator)
                    {
                        if (file_content_validator.ValidateInputFormat(first_delimited_val, sec_delimited_val)
                            != BitcoinExchangeValidator::SUCCESS)
                        {
                            return false;
                        }
                    }

                    std::string ws_clean_first_val = CleanStringWhiteSpaces(first_delimited_val);
                    std::string ws_clean_second_val = CleanStringWhiteSpaces(sec_delimited_val);
                    if (!header_is_validated)
                    {
                        if (file_content_validator.ValidateHeaders(ws_clean_first_val, ws_clean_second_val) 
                            != BitcoinExchangeValidator::SUCCESS)
                        {
                            return false;
                        }
                        header_is_validated = true;
                    }
                    else
                    {
                        BitcoinExchangeValidator::ValidationResult res = BitcoinExchangeValidator::SUCCESS;
                        res = file_content_validator.ValidateDate(ws_clean_first_val); 
                        
                        float exchange_rate = 0;
                        if (res == BitcoinExchangeValidator::SUCCESS)
                        {
                            res = file_content_validator.ValidateAndConvertFloatInput(ws_clean_second_val, exchange_rate);
                        }

                        if (!(this->*callback)(res, ws_clean_first_val, exchange_rate))
                        {
                            return false;
                        }
                    }
                }
            }
            catch (const std::exception& e)
            {
                std::cout << "Error reading '" << file_config.filename << "'.\n";
                return false; 
            }

            return true;
        }

    
        std::map<std::string, float> bitcoin_db_;
};

#endif
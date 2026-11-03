#include <iostream>
// #include "BitcoinExchange/include/BitcoinExchange.hpp"
#include <fstream>
#include <map>
#include <cfloat>
#include <algorithm>

using Date = std::string;
using ExchangeRate = float;

namespace
{
	const size_t kNumberOfHeaders = 2;
	const std::string kDateFieldHeader = "date";
	const std::string kExchangeRateHeader = "exchange_rate";
	const std::string kInputValueHeader = "value";
	const char kBitcoinExchangeRateCsvFileSeparator = ',';
	const char kInputCsvFileSeparator = '|';
	const std::map<int, int> month_days_map;

	template <typename MapKeyType, typename MapValueType>
	struct CsvData
	{
		std::string header1;
		std::string header2;
		std::map<MapKeyType, MapValueType> data_map;
	};

	struct InputData
	{

	};

	bool ReadLineFromStream(std::ifstream& stream, std::string& line)
	{
		if (std::getline(stream, line))
		{
			return true;
		}
		return false;
	}

	bool ConverStringToFloat(const std::string& str, float& value)
	{        
		char* end_ptr = NULL;
		errno = 0;
		double result = std::strtod(str.c_str(), &end_ptr);
		if (end_ptr == str.c_str() || *end_ptr != '\0')
		{
			std::cout << "Error converting\n";
			return false;
		}
		if (errno == ERANGE || result > FLT_MAX || result < -FLT_MAX)
		{   
			std::cout << "Error converting, result out of range\n";
			return false;
		}
		
		value = static_cast<float>(result);
		
		return true;
	}

	bool ValidateExchangeRateByDateHeaders(const std::string& date, const std::string& exchange_rate)
	{
		// Validate headers
		if (date != kDateFieldHeader || exchange_rate != kExchangeRateHeader)
		{
			std::cout << "File headers: " 
			<< date << "', '" << exchange_rate
			<< "' mismatch the expected headers: '"
			<< kDateFieldHeader << "', '" << kExchangeRateHeader
			<< "'\n";
			return false;
		}

		return true;
	}

	bool HasOnlyDigits(const std::string& str)
	{
		for (size_t i = 0; i < str.size(); ++i)
		{
			if (!std::isdigit(static_cast<int>(str[i])))
			{
				return false;
			}
		}
		return true;
	}

	int GetMonthMaxDays(const int year, const int month)
	{
		int max_days = 0;

		if (month == 2)
		{
			// Check is leap year
			if (year % 400 || (year % 4 == 0 && year % 100 != 0))
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
	
	// Return true if date provided is valid, else return false
	// Expected date format: Year-Month-Day 
	bool ValidateDate(const std::string& date)
	{
		const size_t expected_date_size = 10;
		if (date.size() != expected_date_size)
		{
			return false;
		}

		const char expected_separator = '-';
		
		const size_t expected_first_separator_pos = 4;
		const char first_separator = date[expected_first_separator_pos];
		if (first_separator != expected_separator)
		{
			std::cout << "Error, Date first separator: '" << first_separator 
					  << "' mismatch the expected separator: '"  << expected_separator
					  << "'\n";
			return false;
		}

		const size_t expected_sec_separator_pos = 7;
		const char sec_separator = date[expected_sec_separator_pos];
		if (sec_separator != expected_separator)
		{
			std::cout << "Error, Date second separator: '" << first_separator 
					  << "' mismatch the expected separator: '"  << expected_separator
					  << "'\n";
			return false;
		}

		// Validate year
		const std::string& year_str = date.substr(0, expected_first_separator_pos);
		float year = 0;
		if (!HasOnlyDigits(year_str) || !ConverStringToFloat(year_str, year))
		{
			std::cout << "Error, invalid year '" << year_str << "'\n";
			return false;
		}

		// Validate month
		const size_t month_input_size = 2; 
		const std::string& month_str = date.substr(expected_first_separator_pos + 1, month_input_size);
		float month = 0;
		if (!HasOnlyDigits(month_str) || !ConverStringToFloat(month_str, month))
		{
			std::cout << "Error, invalid month '" << month_str << "'\n";
			return false;
		}

		// Validate day
		const std::string& day_str = date.substr(expected_sec_separator_pos + 1);
		float day = 0;
		if (!HasOnlyDigits(day_str) || !ConverStringToFloat(day_str, day))
		{
			std::cout << "Error, invalid day '" << day_str << "'\n";
			return false;
		}

		// Check date bounds
		if (year < 2009 || (month < 1 || month > 12) || (day < 1 || day > GetMonthMaxDays(year, month)))
		{
			std::cout << "Error validating date: '" << date << "', out of bounds\n";
			return false;
		}

		return true;
	}

	bool ValidateExchangeRate(const float& exchange_rate)
	{
		return true;
	}

	std::string CleanStringWhiteSpaces(const std::string& str)
	{
		std::string::const_iterator begin_it = str.begin();
        std::string::const_iterator end_it = str.end();

		std::string result;
        while (begin_it != end_it && std::isspace(*begin_it))
        {
            ++begin_it;
        }
        if (begin_it == end_it)
        {
            return result;
        }
        while (std::isspace(*(end_it - 1)))
        {
            --end_it;
        }
		result = std::string(begin_it, end_it);
		return result;
	}
};

class BitcoinExchange
{
	public:
		BitcoinExchange() : exchange_rate_by_date_map_()
		{
			
		}
		~BitcoinExchange()
		{}

		bool LoadDatabase(const std::string& csv_db_path)
		{
			std::cout << "Loading database\n";

			if (db_loaded_)
			{
				exchange_rate_by_date_map_.clear();
			}

			std::ifstream db_file_stream(csv_db_path);
			if (!db_file_stream.is_open())
			{
				std::cout << "Error opening '" << csv_db_path << "'\n";
				return false;
			}

			// Parse csv db file fields and save in map
			CsvData<std::string, float> csv_data;
			if (!ParseBitcoinExchangeRateCsvDatabase(db_file_stream, csv_data))
			{
				std::cout << "Error parsing bitcoin exchange rates csv database\n";
				return false;
			}

			// Validate headers
			const std::string& date_header = CleanStringWhiteSpaces(csv_data.header1);
			const std::string& exchange_rate_header = CleanStringWhiteSpaces(csv_data.header2);
			if (!ValidateExchangeRateByDateHeaders(date_header, exchange_rate_header))
			{
				std::cout << "Error loading database, invalid headers\n";
				return false;
			}

			std::map<std::string, float>::const_iterator it = csv_data.data_map.begin();
			while (it != csv_data.data_map.end())
			{
				const std::string& date = CleanStringWhiteSpaces(it->first);
				// Clean date whitespaces
				if (!ValidateDate(date))
				{
					std::cout << "Error loading database, invalid date: '" << date << "'\n";
					return false;
				}

				const float& exchange_rate = it->second;
				if (exchange_rate < 0)
				{
					std::cout << "Error loading database, invalid exchange rate '" 
							  << exchange_rate << "'\n";
					return false;
				}

				++it;
			}
			// Copy csv_data.data map into exchange_rate_by_date_map after full validation.
			exchange_rate_by_date_map_ = csv_data.data_map;
			
			if (!db_loaded_)
			{
				db_loaded_ = true;
			}

			std::cout << "Database loaded from csv file located at: '" << csv_db_path << "'\n";
			return true;
		}

		bool ProcessInputAndDisplayResults(const std::string& input_path)
		{
			if (db_loaded_)
			{
				std::ifstream input_file_stream(input_path);
				if (!input_file_stream.is_open())
				{
					std::cout << "Error opening '" << input_path << "'\n";
					return false;
				}	
			}
		}

	private:
		bool ParseBitcoinExchangeRateCsvDatabase(std::ifstream& db_stream, CsvData<std::string, float>& csv_data)
		{
			{
				std::string line;
				if (!ReadLineFromStream(db_stream, line))
				{
					std::cout << "Error reading line from stream\n";
					return false;
				}
				if (!ParseValuesFromLine(line, kBitcoinExchangeRateCsvFileSeparator, csv_data.header1, csv_data.header2))
				{
					std::cout << "Error parsing headers\n";
					return false;
				}
			}
			{
				for (std::string line; ReadLineFromStream(db_stream, line);)
				{
					std::string date;
					std::string exchange_rate_str;
					if (!ParseValuesFromLine(line, kBitcoinExchangeRateCsvFileSeparator, date, exchange_rate_str))
					{
						std::cout << "Error parsing values from line\n";
						return false;
					}

					// Convert exchange rate str to float and add to map
					float exchange_rate_float = 0;
					if (!ConverStringToFloat(exchange_rate_str, exchange_rate_float))
					{
						std::cout << "Error converting exchange rate string to float\n";
						return false;
					}

					std::pair<std::map<std::string, float>::iterator, bool> map_insertion_result = 
						csv_data.data_map.insert(std::make_pair(date, exchange_rate_float));
					if (!map_insertion_result.second)
					{
						std::cout << "Error inserting entry on map, duplicated key: '" << date << "'\n";
						return false;
					}
				}
			}
			return true;
		}

		bool ParseHeaders(const std::string& line, const char separator, std::string& header1, std::string& header2)
		{
			const size_t separator_pos = FindAndValidateSeparatorPos(line, separator);
			if (separator_pos == std::string::npos)
			{
				std::cout << "Error parsing headers, error finding and validatig line separator position\n";
				return false;
			}

			if (!ParseValuesFromLine(line, separator_pos, header1, header2))
			{
				std::cout << "Error parsing headers, error parsing headers from line\n";
				return false;
			}

			std::cout << "Headers parsed successfully\n";
			return true;
		}

		bool ParseValuesFromLine(const std::string& line, const char separator, std::string& value1, std::string& value2)
		{
			if (line.empty())
			{
				std::cout << "Error parsing values from line, empty line\n";
				return false;
			}

			const size_t separator_pos = FindAndValidateSeparatorPos(line, separator);
			if (separator_pos == std::string::npos)
			{
				std::cout << "Error parsing values, error finding and validatig line separator position\n";
				return false;
			}
			if (!separator_pos || separator_pos == line.size() - 1)
			{
				std::cout << "Error parsing values from line, "
						<< "invalid values separator position\n";
				return false;
			}

			size_t line_begin_pos = 0;
			size_t value1_size = separator_pos;

			value1 = line.substr(line_begin_pos, value1_size);
			value2 = line.substr(separator_pos + 1);

			return true;
		}

		size_t FindAndValidateSeparatorPos(const std::string& line, const char separator)
		{
			// Find separator pos
			size_t current_pos = 0;
			const size_t separator_pos = line.find(separator, current_pos);
			if (separator_pos == std::string::npos)
			{
				std::cout << "Error parsing headers, separator not found\n";
				return std::string::npos;
			}
			// Ensure that dont exists more than one separator
			if (line.find(separator, separator_pos + 1) != std::string::npos)
			{
				std::cout << "Error parsing headers, only two headers allowed\n";
				return std::string::npos;
			}

			return separator_pos;
		}
		
		std::map<Date, ExchangeRate> exchange_rate_by_date_map_;
		bool db_loaded_;



};  

int main()
{
	BitcoinExchange btc;

	btc.LoadDatabase("data.csv");

	// if (!btc.Initialize("data.csv"))
	// {
		// return 1;
	// }

	// read input and display results

	return 0;
}
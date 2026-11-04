#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>

class FileParser
{
	public:
		FileParser(const std::string& filename, const char key_value_separator) 
			: file_(filename), key_value_separator_(key_value_separator)
		{
			if (!file_.is_open())
			{
				throw std::runtime_error("Error opening file");
			}
		}
		
		~FileParser()
		{
		}

		bool ParseHeaders(std::string& key_header, std::string& value_header)
		{
			// Parse key value headers
			if (!ParseLineValuesFromSeparator(key_header, value_header))
			{
				return false;
			}

			return true;
		}

		bool ParseKeyValueInputs(std::string& key_input, std::string& value_input)
		{
			// Parse key value headers
			if (!ParseLineValuesFromSeparator(key_input, value_input))
			{
				return false;
			}
			
			return true;
		}
	private:
		FileParser()
		{}

		std::string ReadLine()
		{
			std::string line;
			std::getline(file_, line);

			return line;
		}

		bool ParseLineValuesFromSeparator(std::string& val1,
										  std::string& val2)
		{
			std::string line = ReadLine();
			if (line.empty())
			{
				return false;
			}

			// Parse key value headers
			const size_t line_begin = 0;
			const size_t separator_pos = line.find(key_value_separator_, line_begin);
			if (separator_pos == std::string::npos)
			{
				std::cout << "Error: separator '" 
						  << key_value_separator_ 
						  << "' not found\n";
				return false;
			}
			val1 = line.substr(0, separator_pos);
			val2 = line.substr(separator_pos + 1);
			
			return true;
		}

		std::ifstream file_;
		char key_value_separator_;

};

class BitcoinExchange
{
    public:
        BitcoinExchange() : bitcoin_db_()
        {
			std::cout << "BitcoinExchange default ctor called\n";
        }

        ~BitcoinExchange()
        {
			std::cout << "BitcoinExchange dtor called\n";
        }

		// Load csv database
		bool LoadCsvDatabase(const std::string& csv_filename)
		{
			// Read csv database lines
			try
			{
				const char separator = ',';
				FileParser parser(csv_filename, separator);

				// Read headers
				{
					std::string key_header;
					std::string value_header;
					if (!parser.ParseHeaders(key_header, value_header))
					{
						std::cout << "Error: reading headers\n";
						return false;
					}

					std::cout << "Parsed headers: "
							  << "key header: '" << key_header << "' "
							  << "value_header: '" << value_header << "'\n";
		
					// Validate headers
				}
				// Read inputs
				{
					
					std::string key_input;
					std::string value_input;
					while (parser.ParseKeyValueInputs(key_input, value_input))
					{
						std::cout << "Parsed inputs: "
    						  << "key input: '" << key_input << "' "
    						  << "value input: '" << value_input << "'\n";
					}
				}
			}
			catch (const std::exception& e)
			{
				std::cout << "Error reading '" << csv_filename << "'\n";
				return false; 
			}

			if (bitcoin_db_.empty())
			{
				std::cout << "Error: csv bitcoin database is empty\n";
				return false;
			}

			return true;
		}
    private:
		std::map<std::string, float> bitcoin_db_;
};

#endif
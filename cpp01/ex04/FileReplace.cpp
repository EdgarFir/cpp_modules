#include "FileReplace.hpp"

FileReplace::FileReplace(std::string infile_name, const std::string &to_replace, const std::string &will_replace) 
	: _to_replace(to_replace), _will_replace(will_replace)
{
	std::string outfile_name;

	if (_to_replace.empty())
		throw std::runtime_error("Error: String to replace cannot be empty");

	_infile.open(infile_name.c_str());

	// Ensure theres no error in file open
	if (!_infile.is_open())
		throw std::runtime_error("Error: Opening " + infile_name);

	// Check if file is empty
	if (this->_infile.peek() == EOF)
		throw std::runtime_error("Error: Empty file");

	// Create replace filename with suffix ".replace"
	outfile_name = infile_name.append(".replace");

	// Open file for writing -> ofstream object
	_outfile.open(outfile_name.c_str());

	// Ensure theres no error in outfile open
	if (!_outfile.is_open())
		throw std::runtime_error("Error: opening " + outfile_name);
}

FileReplace::~FileReplace()
{
	// Although ifstream and ofstream automatically close files in Destructor
	// For safety reasons we close anyway in FileReplace Destructor
	if (_infile.is_open()) _infile.close();
	if (_outfile.is_open()) _outfile.close();
}

/**
 * @brief Check in infile for string to replace and swap with string that will replace. 
 */
void FileReplace::replace()
{
	std::string line;
	size_t		pos,
				to_replace_size = this->_to_replace.size(),
				will_replace_size = this->_will_replace.size();

	// Seek lines while not EOF
	while (getline(this->_infile, line))
	{
		// Replace all occurences of to_replace for will_replace inside line
		pos = 0;
		while (1)
		{
			// Find pos of to_replace in line
			pos = line.find(this->_to_replace, pos);
			
			// Ensure line has occurences of to_replace in line, else stop
			if (pos == std::string::npos)
				break ;
			
			// Erase to_replace from line
			line.erase(pos, to_replace_size);

			// Insert will_replace in line
			line.insert(pos, this->_will_replace);

			pos += will_replace_size;
		}
		// Write line to outfile
		this->_outfile << line;

		if (!this->_infile.eof()) this->_outfile << "\n";
	}
}

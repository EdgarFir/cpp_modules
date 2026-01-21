#ifndef FILEREPLACE_HPP

#define FILEREPLACE_HPP

#include <iostream>
#include <fstream>
#include <string>

class FileReplace {
	private:
		const std::string		&_to_replace;
		const std::string		&_will_replace;
		std::ifstream			_infile;
		std::ofstream			_outfile;

	public:
		FileReplace();
		FileReplace(const std::string infile_name, const std::string &to_replace, const std::string &will_replace);
		~FileReplace();
		void	replace();
};


#endif

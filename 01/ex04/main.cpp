#include "FileReplace.hpp"

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr
			<< "Error: " 
			<< "Usage: ./program infilename str_to_replace str_will_replace\n";
		return 1;
	}

	std::string infile_name = argv[1];
	std::string to_replace = argv[2], will_replace = argv[3];

	try
	{
		FileReplace fr(infile_name, to_replace, will_replace);
		fr.replace();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}
	return 0;
}

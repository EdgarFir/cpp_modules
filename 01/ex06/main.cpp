#include "Harl.hpp"

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./HarlFilter level" << "\n";
		return 1;
	}
	
    Harl h;

	h.filter(argv[1]);
}

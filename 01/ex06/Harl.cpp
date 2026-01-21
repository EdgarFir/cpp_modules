#include "Harl.hpp"

Harl::Harl() {}

Harl::~Harl() {}

/**
 * @brief Print debug message.
 */
void Harl::debug( void )
{
   	std::cout << "[ DEBUG ]" <<  "\n";
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << "\n";

}

/**
 * @brief Print info message.
 */
void Harl::info( void )
{
    std::cout << "[ INFO ]" <<  "\n";
    std::cout << "I cannot believe adding extra bacon costs more money.\
 You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << "\n";
}

/**
 * @brief Print warning message.
 */
void Harl::warning( void )
{
	std::cout << "[ WARNING ]" <<  "\n";
    std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years,\
 whereas you started working here just last month." << "\n";
}

/**
 * @brief Print error message.
 */
void Harl::error( void )
{
    std::cout << "[ ERROR ]" << "\n";
    std::cout << "This is unacceptable! I want to speak to the manager now." << "\n";

}

/**
 * @brief Check if level is valid and if so call all functions from that level till last level.
 * 
 * @param level Level fo filter.
 */
void Harl::filter(std::string level)
{
	int level_index = 0;
	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void        (Harl::*funcs[])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

	for (int i = 0; i < 4; i++)
	{
		if (levels[i] == level)
			break ;
		level_index++;
	}

	switch(level_index)
	{
		case 0:
			(this->*funcs[0])();
			// fall through
		case 1:
			(this->*funcs[1])();
			// fall through
		case 2:
			(this->*funcs[2])();
			// fall through
		case 3:
			(this->*funcs[3])();
			break ;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]\n";
	}
	return ;

}

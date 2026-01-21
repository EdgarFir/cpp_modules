#include "PhoneBook.hpp"
#include "Contact.hpp"

/**
 * @brief Print Phonebook intro.
 */
void    intro()
{
    std::cout << "******************************\n";
    std::cout << "******************************\n";
    std::cout << "*                            *\n";
    std::cout << "*         PHONEBOOK          *\n";
    std::cout << "*                            *\n";
    std::cout << "******************************\n";
    std::cout << "******************************\n\n";

}

int main (void) 
{
    PhoneBook   phoneBook;
    std::string option;

    intro();

	while (1)
	{
		std::cout << "******************************\n";
        std::cout << "*          OPTIONS           *\n";
        std::cout << "******************************\n";
        std::cout << "*      ADD * SEARCH * EXIT   *\n";
        std::cout << "******************************\n";
        std::cout << "******************************\n";

        std::cout << "\n>> Type option: ";
        std::getline(std::cin, option);

        if (std::cin.eof())
            exit(0);

		if (option == "ADD")
			phoneBook.addContact();
		else if (option == "SEARCH")
			phoneBook.searchContacts();
		else if (option == "EXIT")
			break ;
        else
            std::cout << "Type a valid option\n";
	}
	std::cout << "\n";
}
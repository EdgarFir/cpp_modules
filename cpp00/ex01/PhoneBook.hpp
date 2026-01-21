#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <sstream>
#include <cstdlib>
#include <iomanip>

#define MAX_CONTACTS 8

class PhoneBook {
public:
    PhoneBook();
    ~PhoneBook();

    void	addContact();
    bool 	showContactInfo(std::string index);
    void	searchContacts();

private:
    Contact     _list[MAX_CONTACTS];
    int			_nbContacts;
	int			_lastContactIndexAdded;
};

#endif

#include "PhoneBook.hpp"
#include <iostream>

PhoneBook::PhoneBook() : _nbContacts(0), _lastContactIndexAdded(0)
{
    std::cout << "******************************\n";
	std::cout << "*    PHONEBOOK TURNED ON     *\n";
	std::cout << "******************************\n\n";
}

PhoneBook::~PhoneBook()
{
    std::cout << "******************************\n";
	std::cout << "*    PHONEBOOK TURNED OFF    *\n";
	std::cout << "******************************\n\n";
}

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int is_empty_str(std::string str)
{
	size_t str_size;
	size_t i;

	str_size = str.size();
	if (!str_size)
		return 1;

	i = 0;
	while (isspace(str[i]))
		i++;
	if (i == str_size)
		return 1;
	return 0;
}

int is_valid_phonenbr(std::string phonenbr)
{
	size_t phonenbr_size;

	phonenbr_size = phonenbr.size();
	if (phonenbr_size != 9)
		return 0;

	for (size_t i = 0; i < phonenbr_size; i++)
	{
		if (!isdigit(phonenbr[i]))
			return 0;
	}
	return 1;
}

std::string getPromptRes(std::string prompt, int validate_phonenbr)
{
	std::string res;

	while (1)
	{
		std::cout << prompt;
		std::getline(std::cin, res);
		if (std::cin.eof())
			exit(0);
		if (is_empty_str(res))
		{
			std::cout << "Empty fields are not accepted\n";
			continue ;
		}
		if (validate_phonenbr && !is_valid_phonenbr(res))
		{
			std::cout << "Invalid phonenumber\n";
			continue ;
		}
		break ;
	}
	return res;
}

std::string clean_col_field(std::string field)
{
	std::string clean_field;
	size_t 		curr_index;
	size_t		word_len;
	int			first_word;

	first_word = 1;
	curr_index = 0;
	while (curr_index < field.size())
	{
		while (curr_index < field.size() && is_space(field[curr_index]))
			curr_index++;
		if (curr_index == field.size())
			break ;
		if (!first_word)
			clean_field.insert(clean_field.size(), " ");
		word_len = 0;
		while (curr_index + word_len < field.size() && !is_space(field[curr_index + word_len]))
			word_len++;
		clean_field = clean_field.insert(clean_field.size(), field.substr(curr_index, word_len));
		if (first_word)
			first_word = 0;
		curr_index += word_len;
	}
	return clean_field;
}

void printCol(std::string field, int colIndex)
{

	std::string clean_field = clean_col_field(field);

	if (clean_field.size() > 10) clean_field = clean_field.substr(0, 9) + ".";

	std::cout << std::setw(10) << clean_field;

	if (colIndex != 3)
		std::cout << "|";
	else
		std::cout << "\n";
}

bool PhoneBook::showContactInfo(std::string index)
{
	// Confirmar se index tem len=1 e se char e um digito
	if (index.size() != 1 || !isdigit(index[0]))
	{
		std::cout << "Invalid index\n";
		return false;
	}
	
	// Converter index para inteiro
	int nIndex = index[0] - '0';

	// Confirmar se numero esta entre 0 e 7
	if (!(nIndex >= 0 && nIndex <= MAX_CONTACTS - 1))
	{
		std::cout << "Invalid index range\n";
		return false;
	}

	// Confirmar se contacto existe
	if (_nbContacts == 0 || (nIndex + 1 > _nbContacts))
	{
		std::cout << "Contact does not exist\n";
		return false;
	}

	std::cout << "\n";

	std::cout 
		<< "Index: " << _list[nIndex].getId() << "\n"
		<< "First name: " << _list[nIndex].getFirstName() << "\n"
		<< "Last name: " << _list[nIndex].getLastName() << "\n"
		<< "Nickname: " << _list[nIndex].getNickname() << "\n"
		<< "Darkest secret: " << _list[nIndex].getDarkestSecret() << "\n"
		<< "Phonenumber: " << _list[nIndex].getPhonenumber() << "\n"
	<< "\n";

	return true;
}

void PhoneBook::searchContacts()
{
	std::cout << "******************************\n";
	std::cout << "*        SEARCH CONTACT      *\n";
	std::cout << "******************************\n\n";

	printCol("Index", 0);
	printCol("First name", 1);
	printCol("Last name", 2);
	printCol("Nickname", 3);
	
	for (int i = 0; i < _nbContacts; i++)
	{
		// Criar objecto osstream
		std::ostringstream stream;
	
		stream << _list[i].getId(); // Enviar id para esse objeto
		printCol(stream.str(), 0); // Converte lo para string
		printCol(_list[i].getFirstName(), 1);
		printCol(_list[i].getLastName(), 2);
		printCol(_list[i].getNickname(), 3);
	}
	
	while (1)
	{
		if (showContactInfo(getPromptRes("\n>> Type contact index to show information: ", 0)))
			break ;
	}
}

void PhoneBook::addContact()
{
	Contact new_contact;

	std::cout << "\n";
	std::cout << "******************************\n";
	std::cout << "*        ADD CONTACT         *\n";
	std::cout << "******************************\n\n";


	new_contact.setFirstName(getPromptRes(">> First name: ", 0));
	new_contact.setLastName(getPromptRes(">> Last name: ", 0));
	new_contact.setNickname(getPromptRes(">> Nickname: ", 0));
	new_contact.setDarkestSecret(getPromptRes(">> Darkest secret: ", 0));
	new_contact.setPhonenumber(getPromptRes(">> Phonenumber: ", 1));
	new_contact.setId(_lastContactIndexAdded % MAX_CONTACTS);

	_list[_lastContactIndexAdded] = new_contact;
	_lastContactIndexAdded = (_lastContactIndexAdded + 1) % MAX_CONTACTS;
	if (_nbContacts < MAX_CONTACTS)
		_nbContacts++;
	std::cout << "\n** Contact added with success **\n\n"; 
}

#include "Contact.hpp"

std::string Contact::getFirstName() const {
    return _first_name;
}

std::string Contact::getLastName() const {
    return _last_name;
}

std::string Contact::getNickname() const {
    return _nickname;
}

std::string Contact::getDarkestSecret() const {
    return _darkest_secret;
}

int Contact::getId(void) const {
	return _id;
}

std::string Contact::getPhonenumber(void) const {
	return _phonenumber;
}

void Contact::setFirstName(const std::string &first_name) {
    _first_name = first_name;
}


void Contact::setLastName(const std::string &last_name) {
    _last_name = last_name;
}

void Contact::setNickname(const std::string &nickname) {
    _nickname = nickname;
}

void Contact::setDarkestSecret(const std::string &darkest_secret) {
    _darkest_secret = darkest_secret;
}

void Contact::setPhonenumber(const std::string &phonenumber) {
	_phonenumber = phonenumber;
}

void Contact::setId(const int &id) {
	_id = id;
}

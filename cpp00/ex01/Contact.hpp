#ifndef CONTACT_HPP

# define CONTACT_HPP

#include <iostream>

class Contact 
{
    private:
        std::string _first_name;
        std::string _last_name;
        std::string _nickname;
        std::string _darkest_secret;
        std::string _phonenumber;
        int         _id;

    public:
        std::string getFirstName() const;
        std::string getNickname() const;
        std::string getLastName() const;
        std::string getDarkestSecret() const;
		std::string getPhonenumber() const;
		int			getId(void) const;

        void        setFirstName(const std::string &first_name);
        void        setLastName(const std::string &last_name);
        void        setNickname(const std::string &nickname);
        void        setDarkestSecret(const std::string &darkest_secret);
		void		setPhonenumber(const std::string &phonenumber);
		void 		setId(const int &id);
};

#endif
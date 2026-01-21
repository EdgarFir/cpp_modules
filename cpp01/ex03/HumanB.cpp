#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL)
{}

/**
 * @brief Print HumanB attack message if HumanB is armed.
 */
void	HumanB::attack( void )
{
	if (!_weapon) { std::cout << "Human: " << _name << " is not armed.\n"; return ; }
	
	std::cout << this->_name << " attacks with their " << this->_weapon->getType() << "\n";
}

/**
 * @brief Arm HumanB with Weapon.
 * 
 * @param _weapon Weapon object to assign to HumanB.
 */
void	HumanB::setWeapon(Weapon &_weapon)
{
	this->_weapon = &_weapon;
}

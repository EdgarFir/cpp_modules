#include "Zombie.hpp"

Zombie::Zombie(std::string name) : _name(name)
{}

Zombie::~Zombie()
{
    std::cout << _name << " died...\n";
}

/**
 * @brief Print Zombie message.
 */
void Zombie::announce( void )
{
    std::cout << _name << ": BraiiiiiiinnnzzzZ...\n";
}

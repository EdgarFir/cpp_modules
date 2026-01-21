#include "Zombie.hpp"

/**
 * @brief Allocates new Zombie in the heap memory and returns it.
 * 
 * @param name Name of the zombie.
 * 
 * @return Zombie allocated.
 */
Zombie* newZombie( std::string name )
{
    Zombie* zombie = new Zombie(name); 

    return zombie;
}

#include "Zombie.hpp"

/**
 * @brief Create a Zombie on the memory stack and call announce().
 * 
 * @param name Name of the zombie.
 */
void randomChump( std::string name )
{
    Zombie zombie(name);

    zombie.announce();
}

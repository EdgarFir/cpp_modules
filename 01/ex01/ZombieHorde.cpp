#include "Zombie.hpp"

/**
 * @brief Allocates N Zombies in the heap memory and returns it.
 * 
 * @param N Number of Zombies to allocate.
 * @param name Name of the Zombies.
 * 
 * @return Array of Zombies allocated if N is higher than 0, else NULL.
 */
Zombie* zombieHorde( int N, std::string name )
{
    if (N <= 0)
        return NULL;

    Zombie *horde = new Zombie[N];

    for (int i = 0; i < N; i++)
        horde[i].setName(name);
    return horde;
}

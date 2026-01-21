#include "Zombie.hpp"

int main()
{
    Zombie *zombie = newZombie("Edgar");
    randomChump("Fred");

    zombie->announce();
    
    delete zombie;
    return 0;
}

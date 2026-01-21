#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
	{
		Weapon club = Weapon("crude spiked club");
		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");
		HumanB jim("Jim");
		// jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}
	{
		Weapon *club = new Weapon("crude spiked club");
		HumanB jim("Jim");
		jim.setWeapon(*club);
		jim.attack();
		club->setType("some other type of club");
		jim.attack();

		delete club;
	}
	{
		Weapon *club = new Weapon("crude spiked club");
		HumanB jim("Jim");
		jim.attack();
		club->setType("some other type of club");
		jim.attack();

		delete club;
	}
	return 0;
}

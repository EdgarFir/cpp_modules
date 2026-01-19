#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <cstdlib>

/**
 * @brief Select randomly a number from 1 to 3 and return an allocated Base inherited class: A, B or C.
 * 
 * @return If number randomly picked is equal to 1 returns allocated A class object, 
 * 2 - returns allocated B class object or 3 - a allocated C class object.
 */
Base * generate(void) {
	int random_class = (rand() % 3) + 1;

	switch (random_class)
	{
		case 1:
			return new A;
		case 2:
			return new B;
		case 3:
			return new C;
	}
	return NULL;
}

/**
 * @brief Identify class inherited from Base through a pointer and print.
 * 
 * @param p Base class object pointer.
*/
void identify(Base *p) {
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "A\n";
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << "B\n";
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << "C\n";
	else
		std::cout << "Invalid Base inherited class\n";
}

/**
 * @brief Identify class inherited from Base through a reference and print.
 * 
 * @param p Base class object reference.
 */
void identify(Base &p) {
	try {
		dynamic_cast<A&>(p);
		std::cout << "A\n";
		return ;
	}
	catch (std::runtime_error & e) {}

	try {
		dynamic_cast<B&>(p);
		std::cout << "B\n";
		return ;
	}
	catch (std::runtime_error & e) {}
	
	try {
		dynamic_cast<C&>(p);
		std::cout << "C\n";
		return ;
	}
	catch (std::runtime_error & e) {
	}
	std::cout << "Invalid Base inherited class\n";
}

int main() {
	srand(time(NULL));
	Base *a = generate();
	std::cout << "Ptr Identify: "; identify(a);
	std::cout << "Ref Identify: "; identify(a);
	delete a;
}
#include "../includes/Base.hpp"
#include "../includes/A.hpp"
#include "../includes/B.hpp"
#include "../includes/C.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Base * generate(void) {
    int res = rand() % 3;

    switch (res) {
        case 0: return new A();
        case 1: return new B();
        case 2: return new C();
        default: break ;
    }
    return NULL;
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p) != NULL) std::cout << "A\n";
    if (dynamic_cast<B*>(p) != NULL) std::cout << "B\n";
    if (dynamic_cast<C*>(p) != NULL) std::cout << "C\n";    
}

void identify(Base& p) {
    try {
        dynamic_cast<A&>(p);
        std::cout << "A\n";
        return ;
    }
    catch (const std::bad_cast & e) {}

    try {
        dynamic_cast<B&>(p);
        std::cout << "B\n";
        return ;
    }
    catch (const std::bad_cast & e) {}

    try {
        dynamic_cast<C&>(p);
        std::cout << "C\n";
        return ;
    }
    catch (const std::bad_cast & e) {}

    std::cout << "Invalid polymorphical class\n";
}

int main() {
    std::srand(time(NULL));

    Base *p = generate();

    identify(p);
    identify(*p);

    delete p;
}

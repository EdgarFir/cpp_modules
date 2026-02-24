#include "../includes/Serializer.hpp"
#include <iostream>

int main() {
    {
        Data d;
    
        d.n = 42;
        uintptr_t dataAdrr = Serializer::serialize(&d);
        Data *deserialized = Serializer::deserialize(dataAdrr);
        
        std::cout << "0x" << std::hex << dataAdrr << std::endl;
        std::cout << &d << std::endl;
        std::cout << deserialized << std::endl;
        std::cout << std::dec << deserialized->n << "\n\n";
    }
    {
        Data *p = new Data();

        p->n = 42;
        std::cout << p->n << std::endl;

        uintptr_t dataAddr = Serializer::serialize(p);

        std::cout << p << std::endl;
        std::cout << "0x" << std::hex << dataAddr << std::endl;
        
        Data *t = Serializer::deserialize(dataAddr);
        
        t->n = 422;
        std::cout << t << std::endl;
        std::cout << std::dec << t->n << std::endl;        
        delete p;
    }
}
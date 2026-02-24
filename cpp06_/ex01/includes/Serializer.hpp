#ifndef SERIALIZER_HPP

#include "Data.h"
#include <cstdint>

# define SERIALIZER_HPP

class Serializer {
    private:
        Serializer();
        Serializer(const Serializer & src);
        Serializer & operator=(const Serializer & src);
    public:

        static uintptr_t serialize(Data * ptr);
        static Data * deserialize(uintptr_t raw);

        ~Serializer();
};

#endif
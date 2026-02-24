#include "../includes/Serializer.hpp"

Serializer::Serializer() {}
Serializer::Serializer(const Serializer & src) { static_cast<void>(src); }
Serializer & Serializer::operator=(const Serializer & src) {
    static_cast<void>(src);
    return *this;
}

uintptr_t Serializer::serialize(Data * ptr) { return (reinterpret_cast<uintptr_t>(ptr)); }

Data * Serializer::deserialize(uintptr_t raw) { return (reinterpret_cast<Data*>(raw)); }

Serializer::~Serializer() {}
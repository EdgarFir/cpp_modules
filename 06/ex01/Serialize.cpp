#include "Serialize.hpp"


Serialize::Serialize() {}

Serialize::Serialize(const Serialize & src) {
	static_cast<void>(src);
}

Serialize &Serialize::operator=(const Serialize & src) {
	static_cast<void>(src);
	return *this;
}

Serialize::~Serialize() {}

uintptr_t Serialize::serialize(Data * ptr) {
	if (!ptr)
		return 0;
	return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serialize::deserialize(uintptr_t raw) {
	if (!raw)
		return 0;
	return reinterpret_cast<Data *>(raw);
}

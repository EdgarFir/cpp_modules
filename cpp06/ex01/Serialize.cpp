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

/**
 * @brief Convert a pointer to Data into uintptr_t that represents his memory address,
 * without copy or serializing data.
 * 
 * @param ptr Pointer to struct Data.
 * 
 * @return uintptr_t value that represents pointer memory address.
 * 		   If pointer is NULL, returns 0.
 */
uintptr_t Serialize::serialize(Data * ptr) {
	if (!ptr)
		return 0;
	return reinterpret_cast<uintptr_t>(ptr);
}


/** 
 * @brief Convert the uintptr_t type value back to a pointer to Data.
 * This function reinterpret a int value that represents an memory address and
 * returns a pointer to Data. Any object is created, copied or validated, the memory adress
 * is just reused.
 * 
 * @param raw uintptr_t value type that represents a memory address.
 * 
 * @return Pointer to Data corresponding to the given address. If raw is 0 returns NULL.
 * 
 * @warning The raw value passed must be an object that coexists in the same memory space 
 * and must be a valid Data memory address.
 */
Data *Serialize::deserialize(uintptr_t raw) {
	if (!raw)
		return 0;
	return reinterpret_cast<Data *>(raw);
}

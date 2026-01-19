#include "Serialize.hpp"
#include <iostream>

int main() {
	std::cout << "==== Testing Serialization ====\n\n";

	Data *d = new Data;
	
	d->val = 42;
	std::cout << "Original ptr address = " << d << std::endl;

	std::cout << "Serializing d..\n";
	uintptr_t uint_serialized = Serialize::serialize(d);
	std::cout << "Serialized value = 0x" << std::hex << uint_serialized << std::endl;

	std::cout << "Deserializing d..\n";
	std::cout << "Deserialized value = " << Serialize::deserialize(uint_serialized) << std::endl;
}
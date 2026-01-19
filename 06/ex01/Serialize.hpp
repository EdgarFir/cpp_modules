#ifndef SERIALIZE_HPP

# define SERIALIZE_HPP

#include <stdint.h>
#include "Data.h"

class Serialize {
	private:
		Serialize();
		Serialize(const Serialize & src);
		Serialize &operator=(const Serialize & src);
		~Serialize();
	public:
		static uintptr_t serialize(Data * ptr);
		static Data *deserialize(uintptr_t raw);
};

#endif
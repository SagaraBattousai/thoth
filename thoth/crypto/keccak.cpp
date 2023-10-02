
//#include <vector>

#include <thoth/keccak.h>

namespace thoth
{
	hash_output Keccak224(hash_input input)
	{
		hash_output out(28); // should be size of vector, original code lost so rewrite
		keccak224(
			reinterpret_cast<const std::uint8_t*>(input.data()),
			(int) input.size(),
			reinterpret_cast<std::uint8_t*>(out.data())
		);
		return out;
	}

	hash_output Keccak256(hash_input input)
	{
		hash_output out(32);
		keccak256(
			reinterpret_cast<const std::uint8_t*>(input.data()),
			(int) input.size(),
			reinterpret_cast<std::uint8_t*>(out.data())
		);
		return out;
	}

	hash_output Keccak384(hash_input input)
	{
		hash_output out(48);
		keccak384(
			reinterpret_cast<const std::uint8_t*>(input.data()),
			(int) input.size(),
			reinterpret_cast<std::uint8_t*>(out.data())
		);
		return out;
	}

	hash_output Keccak512(hash_input input)
	{
		hash_output out(64);
		keccak512(
			reinterpret_cast<const std::uint8_t*>(input.data()),
			(int) input.size(),
			reinterpret_cast<std::uint8_t*>(out.data())
		);
		return out;

	}
}

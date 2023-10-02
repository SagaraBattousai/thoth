
#include <thoth/hash.h>

namespace thoth
{

	HashFunction operator*(HashFunction&& lhs, HashFunction&& rhs)
	{
		return [g = std::move(lhs), f = std::move(rhs)]
		(hash_input data)
		{
			return g(f(data));
		};
	}

} //namespace thoth

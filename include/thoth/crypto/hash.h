#ifndef __THOTH_CRYPTO_HASH_H__
#define __THOTH_CRYPTO_HASH_H__

#include <cstddef>

#include <vector>
#include <functional>

#include <_thoth_config.h>

namespace thoth
{

    using hash_output = std::vector<std::byte>;
    // don't like using const and/or ref inside of using/typedef
    using hash_input = const std::vector<std::byte>&;

		using HashFunction = std::function<hash_output(hash_input)>;

    //Function Composition
		THOTH_EXPORT HashFunction operator*(HashFunction&& lhs, HashFunction&& rhs); 

} //namespace thoth

#endif

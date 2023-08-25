#ifndef __THOTH_CONCEPTS_H__
#define __THOTH_CONCEPTS_H__

#include<concepts>

namespace thoth
{
	template<typename U, typename T>
	concept Addable = requires(T a, U b)
	{
		{ a + b } -> std::convertible_to<T>;
	};

	template<typename U, typename T>
	concept Multiplyable = requires(T a, U b)
	{
		{ a* b } -> std::convertible_to<T>;
	};

	template<typename U, typename T>
	concept Comparable = requires(T a, U b)
	{
		{ a <=> b } -> std::convertible_to<bool>;
	};


}

#endif
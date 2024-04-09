
#include <thoth/core/orphan_core-integral.h>

void 
integral_add(integral_digit* div, const integral_digit* lhs,
	int lhs_size, const integral_digit* rhs, int rhs_size)
{
	//Note adding two max 30 bit numbers = max 31 bit number - 1 (since even)
	integral_digit carry = 0;

	if (lhs_size < rhs_size)
	{
		int temp = lhs_size;
		lhs_size = rhs_size;
		rhs_size = temp;

		const integral_digit* tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}

	this->set_digits(size_a + 1);

	integral::size_type iter;

	for (iter = 0; iter < size_b; ++iter)
	{
		carry += (*a)[iter] + (*b)[iter];
		this->digits[iter] = carry & INTEGRAL_MASK;
		carry >>= INTEGRAL_SHIFT;
	}
	//TODO: skip when carry is 0

	for (; iter < size_a; ++iter)
	{
		carry += (*a)[iter];
		this->digits[iter] = carry & INTEGRAL_MASK;
		carry >>= INTEGRAL_SHIFT;
	}
	this->digits[iter] = carry;

	return *this;
}
}

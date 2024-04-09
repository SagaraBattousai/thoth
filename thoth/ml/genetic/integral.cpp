#include <thoth/integral.h>

namespace
{
	template<typename T, typename S>
	inline void SwapIntegrals(T *a, T *b, S *size_a, S *size_b)
	{
		S *size_temp = size_a;
		size_a = size_b;
		size_b = size_temp;

		const T *temp = a;
		a = b;
		b = temp;
	}

}

namespace thoth
{
	integral_digit
		digit_div_rem(integral_t *div, const integral_t *lhs, int lhs_size, const integral_digit rhs)
	{
		return rhs;
	}

	Integral::Integral(unsigned long long n, std::int8_t sign)
		: sign{ sign }
	{
		if (n == 0)
		{
			//Should just use Zero but allows for "negative" zero
			this->digits = integral{ 0 };
		}
		else
		{
			this->digits = integral();
			while (n != 0)
			{
				this->digits.push_back(n % INTEGRAL_BASE);
				n /= INTEGRAL_BASE; //Integer division expected
			}
		}
	}
	/*
		Integral::Integral(std::string hex_string)
		{

		}

		Integral::Integral(const Integral&)
		{

		}
		*/

	Integral &Integral::operator+=(const Integral &rhs)
	{
		const integral *a = &this->digits;
		const integral *b = &(rhs.digits);

		integral::size_type size_a = this->digits.size();
		integral::size_type size_b = rhs.digits.size();

		//Note adding two max 30 bit numbers = max 31 bit number - 1 (since even)
		integral_digit carry = 0;

		if (size_a < size_b)
		{
			SwapIntegrals(a, b, &size_a, &size_b);
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

	Integral operator+(Integral lhs, const Integral &rhs)
	{
		lhs += rhs;
		return lhs;
	}

	Integral &Integral::operator-=(const Integral &rhs)
	{
		return *this;
	}

	Integral operator-(Integral lhs, const Integral &rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	Integral &Integral::operator*=(const Integral &rhs)
	{
		return *this;
	}

	Integral operator*(Integral lhs, const Integral &rhs)
	{
		return lhs;
	}

	Integral &Integral::operator/=(const Integral &rhs)
	{
		return *this;
	}

	Integral operator/(Integral lhs, const Integral &rhs)
	{
		return lhs;
	}

	Integral &Integral::divRem(const Integral &rhs)
	{
		return *this;
	}

	Integral divRem(Integral lhs, const Integral &rhs)
	{
		return lhs;
	}

	Integral &Integral::operator++()
	{
		return *this;
	}

	Integral Integral::operator++(int)
	{
		return Integral::Zero();
	}

	Integral &Integral::operator--()
	{
		return *this;
	}

	Integral Integral::operator--(int)
	{
		return Integral::Zero();
	}

	Integral &Integral::operator%=(const Integral &rhs)
	{
		return *this;
	}

	Integral operator%(Integral lhs, const Integral &rhs)
	{
		return lhs;
	}

	Integral &Integral::operator<<=(int rhs)
	{
		return *this;
	}

	Integral operator<<(Integral lhs, int rhs)
	{
		return Integral::Zero();
	}

	Integral &Integral::operator>>=(int rhs)
	{
		return *this;
	}

	Integral operator>>(Integral lhs, int rhs)
	{
		return Integral::Zero();
	}


	std::ostream &operator<<(std::ostream &os, const Integral &obj)
	{
		//TODO: Just for now, do not leave, do not commit!
		os << (int)obj.digits[0];
		return os;
	}


	void Integral::set_digits(integral::size_type count)
	{
		integral::size_type size_diff = this->digits.size();

		if (size_diff >= count)
			return;

		size_diff = count - size_diff;

		while (size_diff > 0)
		{
			this->digits.emplace_back();
			--size_diff;
		}

	}
}

/* C API Interop (Was this the right choice? Wish I'd saved the old version) */

integral_t *new_integral(unsigned long long absolute)
{
	//Explicit cast required by clang on android
	return new thoth::Integral((unsigned long long) absolute, 1);
}

integral_t *new_unsigned_integral(unsigned long long absolute)
{
	return new thoth::Integral(absolute, 0);
}

void free_integral(integral_t *number)
{
	delete number;
}

integral_t *add_integral(const integral_t *lhs, const integral_t *rhs)
{
	thoth::Integral ret = (*lhs) + (*rhs);
	return new thoth::Integral(ret); //check std::move
}

integral_t *sub_integral(const integral_t *lhs, const integral_t *rhs)
{
	thoth::Integral ret = (*lhs) - (*rhs);
	return new thoth::Integral(ret); //check std::move
}

integral_t *mult_integral(const integral_t *lhs, const integral_t *rhs)
{
	thoth::Integral ret = (*lhs) * (*rhs);
	return new thoth::Integral(ret); //check std::move
}

integral_t *div_integral(const integral_t *lhs, const integral_t *rhs)
{
	thoth::Integral ret = (*lhs) / (*rhs);
	return new thoth::Integral(ret); //check std::move
}

integral_t *div_rem_integral(const integral_t *lhs, const integral_t *rhs)
{
	thoth::Integral ret = divRem(*lhs, *rhs);
	return new thoth::Integral(ret); //check std::move
}

integral_t *mod_integral(const integral_t *lhs, const integral_t *rhs)
{
	thoth::Integral ret = (*lhs) % (*rhs);
	return new thoth::Integral(ret); //check std::move
}

void inc_integral(integral_t *value)
{
	++(*value);
}

void dec_integral(integral_t *value)
{
	--(*value);
}


integral_digit
lshift_integral(integral_digit *dst, const integral_digit *src, int count, int shift);

integral_digit
rshift_integral(integral_digit *dst, const integral_digit *src, int count, int shift);

integral_digit
lshift(integral_digit *dst, const integral_digit *src, int count, int shift)
{
	integral_digit carry = 0;
	double_digit acc;

	for (int i = 0; i < count; ++i)
	{
		acc = ((double_digit)src[i] << shift) | carry;
		dst[i] = (integral_digit)acc & INTEGRAL_MASK;
		carry = (integral_digit)(acc >> INTEGRAL_SHIFT);
	}
	return carry;
}

integral_digit
rshift(integral_digit *dst, const integral_digit *src, int count, int shift)
{
	integral_digit carry = 0;
	integral_digit shift_mask = ((integral_digit)1 << shift) - 1;
	double_digit acc;

	for (int i = count; i >= 0; --i)
	{
		acc = ((double_digit)carry << INTEGRAL_SHIFT) | src[i];
		carry = (integral_digit)acc & shift_mask;
		dst[i] = (integral_digit)(acc >> shift);
	}

	return carry;
}

#ifndef __THOTH_NUMERIC_CORE_INTEGRAL_H__
#define __THOTH_NUMERIC_CORE_INTEGRAL_H__
/** @file
 * Core, low level C
 */

#include <_thoth_config.h>


 /**
	* Typedefs and constant values required for core integral operations.
	* Theses are split for C and C++ (despite not being neccisary) to promote
	* good style.
	*/
#ifdef __cplusplus

#include <cstdint>

	//Originally types were based on processor;
	//However now we will stick to the same on all processors
using integral_digit = std::uint32_t;
using sintegral_digit = std::int32_t;  // Signed digit
using double_digit = std::uint64_t; // Or ddigit like dword?
using sdouble_digit = std::int64_t;  // Signed double_digit

constexpr auto BITS_IN_DIGIT = 30;
constexpr auto INTEGRAL_SHIFT = BITS_IN_DIGIT;
constexpr auto INTEGRAL_DECIMAL_SHIFT = 9; // Max(e such that 10**e fits in a digit)
constexpr integral_digit INTEGRAL_DECIMAL_BASE = 1000000000;  // 10 ** DECIMAL_SHIFT
constexpr integral_digit INTEGRAL_BASE = 0x40000000; // A.K.A (1 << INTEGRAL_SHIFT)
constexpr integral_digit INTEGRAL_MASK = 0x3FFFFFFF; // A.K.A (INTEGRAL_BASE - 1)

#else

#include <stdint.h>

	//Originally types were based on processor;
	//However now we will stick to the same on all processors
typedef uint32_t integral_digit;
typedef int32_t	 sintegral_digit; // Signed digit
typedef uint64_t double_digit;    // Or ddigit like dword?
typedef int64_t  sdouble_digit;   // Signed double_digit

#define BITS_IN_DIGIT          30
#define INTEGRAL_SHIFT         BITS_IN_DIGIT
#define INTEGRAL_DECIMAL_SHIFT 9 // Max(e such that 10**e fits in a digit)
#define INTEGRAL_DECIMAL_BASE  ((integral_digit) 1000000000)  // 10 ** DECIMAL_SHIFT
#define INTEGRAL_BASE          ((integral_digit) 0x40000000) // A.K.A (1 << INTEGRAL_SHIFT)
#define INTEGRAL_MASK          ((integral_digit) 0x3FFFFFFF) // A.K.A (INTEGRAL_BASE - 1)

#endif

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * @brief Divides a large numbers (an array of integral digits) by a single integral digit.
	 * @param[out] div stores the result of dividing lhs by rhs.
	 * @param[in] lhs left hand side.
	 * @param lhs_size left hand side size.
	 * @param rhs right hand side single digit.
	 * @returns remainder of lhs divided by rhs.
	 */
	THOTH_LOCAL integral_digit
		digit_div_rem(integral_digit* div, const integral_digit* lhs, int lhs_size, const integral_digit rhs);


	/**
	 * @brief Adds two large numbers (an array of integral digits).
	 * @param[out] dst stores the result of adding lhs and rhs.
	 * @param[in] lhs left hand side.
	 * @param lhs_size left hand side size.
	 * @param[in] rhs right hand side.
	 * @param rhs_size right hand side size.
	 */
	THOTH_EXPORT void
		integral_add(integral_digit* div, const integral_digit* lhs, int lhs_size, const integral_digit* rhs, int rhs_size);

	/**
	 * @brief Subtracts two large numbers (an array of integral digits).
	 * @param[out] dst stores the result of subtracting lhs by rhs.
	 * @param[in] lhs left hand side.
	 * @param lhs_size left hand side size.
	 * @param[in] rhs right hand side.
	 * @param rhs_size right hand side size.
	 */
	THOTH_EXPORT void
		integral_sub(integral_digit* div, const integral_digit* lhs, int lhs_size, const integral_digit* rhs, int rhs_size);

	/**
	 * @brief Multiplies two large numbers (an array of integral digits).
	 * @param[out] dst stores the result of multiplying lhs and rhs.
	 * @param[in] lhs left hand side.
	 * @param lhs_size left hand side size.
	 * @param[in] rhs right hand side.
	 * @param rhs_size right hand side size.
	 */
	THOTH_EXPORT void
		integral_mult(integral_digit* div, const integral_digit* lhs, int lhs_size, const integral_digit* rhs, int rhs_size);

	/**
	 * @brief Divides two large numbers (an array of integral digits).
	 * @param[out] dst stores the result of dividing lhs by rhs.
	 * @param[in] lhs left hand side.
	 * @param lhs_size left hand side size.
	 * @param[in] rhs right hand side.
	 * @param rhs_size right hand side size.
	 */
	THOTH_EXPORT void
		integral_div(integral_digit* div, const integral_digit* lhs, int lhs_size, const integral_digit* rhs, int rhs_size);

	//integral_t* THOTH_EXPORT div_rem(const integral_t* lhs, const integral_t* rhs);

	//integral_t* THOTH_EXPORT mod(const integral_t* lhs, const integral_t* rhs);

	/**
	 * @brief increments a large number (an array of integral digits).
	 * @param[in,out] value the value to increment.
	 */
	THOTH_EXPORT void integral_inc(integral_digit* value);

	/**
	 * @brief decrements a large number (an array of integral digits).
	 * @param[in,out] value the value to decrement.
	 */
	THOTH_EXPORT void integral_dec(integral_digit* value);

	/**
	 * @brief Computes the left shift of an integral
	 * @pre dst is an array with size >= count.
	 * @pre 0 <= shift < INTEGRAL_SHIFT (otherwise the result is undefined).
	 * @pre 0 <= count <= size of src
	 * @param[out] dst stores the rsult of shifting src shift bits to the left.
	 * @param[in] src contains the data to be shifted.
	 * @param count the size of src array to shift.
	 * @param shift the amount to shift src by.
	 * @return The "shift" bits that were shifted out of the top
	 */
	THOTH_EXPORT integral_digit
		integral_lshift(integral_digit* dst, const integral_digit* src, int count, int shift);

	/**
	 * @brief Computes the right shift of an integral
	 * @pre dst is an array with size >= count.
	 * @pre 0 <= shift < INTEGRAL_SHIFT (otherwise the result is undefined).
	 * @pre 0 <= count <= size of src
	 * @param[out] dst stores the rsult of shifting src shift bits to the right.
	 * @param[in] src contains the data to be shifted.
	 * @param count the size of src array to shift.
	 * @param shift the amount to shift src by.
	 * @return The "shift" bits that were shifted out of the bottom
	 */
	THOTH_EXPORT integral_digit
		integral_rshift(integral_digit* dst, const integral_digit* src, int count, int shift);


#ifdef __cplusplus
}
#endif

#endif

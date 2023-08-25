#ifndef __THOTH_UTILS_H__
#define __THOTH_UTILS_H__

namespace thoth
{
	/*******************************************************************************
	 * A brief history of JavaDoc-style (C-style) banner comments.
	 *
	 * This function will compare two pointers by their respective metrics and set
	 * ptr_a to be the smaller of the two and ptr_b to be the larger (or equal)
	 *
	 * @param ptr_a A pointer to one of the two elements to be compared.
	 *								this will point to the smaller of the two elements when the
	 *								function returns.
	 *
	 * @param ptr_b A pointer to the other element to be compared
	 *								this will point to the larger of the two elements when the
	 *								function returns.
	 *
	 ******************************************************************************/
	//inline void Min(const T *&ptr_a, const T*& ptr_b, const U& metric_a, const U& metric_b)
	template <typename T, typename U>
	inline void Min(const T** ptr_a, const T** ptr_b, const U& metric_a, const U& metric_b)
	{
		if (metric_b < metric_a)
		{
			const T* tmp = *ptr_a;
			*ptr_a = *ptr_b;
			*ptr_b = tmp;
		}
	}
}

#endif
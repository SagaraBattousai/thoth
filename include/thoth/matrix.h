#ifndef __THOTH_MATRIX_H__
#define __THOTH_MATRIX_H__

#include <_thoth_config.h>

#include <vector>
#include <iostream> //may change
#include <numeric>
#include <utility>
#include <stdexcept>

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

	namespace
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
		template <typename T, typename U>
		inline void Min(T*& ptr_a, T*& ptr_b, const U& metric_a, const U& metric_b)
		{
			if (metric_b < metric_a)
			{
				T* tmp = ptr_a;
				ptr_a = ptr_b;
				ptr_b = tmp;
			}
		}
	}

	//template<typename T, int n, int... dims>
	//class Matrix { };

	//template<typename T, int a, int b>
	//class Matrix<T, a, b> { };

	template<typename T>
	class Matrix //Its a header, it doesn't need to be exported
	{
	public:

		using size_type = int;

		constexpr Matrix(std::initializer_list<size_type> dimensions, std::initializer_list<T> values);

		constexpr Matrix(std::initializer_list<size_type> dimensions, const T& value);

		constexpr explicit Matrix(std::initializer_list<size_type> dimensions);

		static constexpr Matrix Zeros(std::initializer_list<size_type> dimensions);

		template<class InputIt>
		constexpr Matrix(std::initializer_list<size_type> dimensions, InputIt first, InputIt last);

		//Could =default as I dont know what im doing but I will try with both 
		constexpr Matrix(Matrix&& other); //is it trivial?

		template<typename V>
		static constexpr Matrix ZerosLike(const Matrix<V>& other);

		template<typename V>
		static constexpr Matrix Like(const Matrix<V>& other);

		constexpr const std::vector<size_type>& Shape() const noexcept { return this->dimensions_; };

		template<CONSTRAINT(Addable<T>) U>
		Matrix& operator+=(const U& scalar);

		template<CONSTRAINT(Addable<T>) U>
		Matrix& operator+=(const Matrix<U>& rhs);

		template<typename V, CONSTRAINT(Addable<V>) U>
		friend Matrix<V> operator+(Matrix<V> matrix, const U& scalar)
		{
			matrix += scalar;
			return matrix;
		};

		template<CONSTRAINT(Addable<T>) U>
		friend Matrix operator+(Matrix lhs, const Matrix<U>& rhs)
		{
			lhs += rhs;
			return lhs;
		};

		template<CONSTRAINT(Multiplyable<T>) U>
		Matrix& operator*=(const U& scalar);

		template<CONSTRAINT(Multiplyable<T>) U>
		Matrix& operator*=(const Matrix<U>& rhs);

		template<typename V, CONSTRAINT(Multiplyable<V>) U>
		friend Matrix<V> operator*(Matrix<V> matrix, const U& scalar)
		{
			matrix *= scalar;
			return matrix;
		};

		template<typename V, CONSTRAINT(Multiplyable<V>) U>
		friend Matrix<V> operator*(Matrix<V> lhs, const Matrix<U>& rhs)
		{
			lhs *= rhs;
			return lhs;
		};


	private:
		constexpr explicit Matrix(const std::vector<size_type>& dimensions);

		constexpr Matrix(const std::vector<size_type>& dimensions, const T& value);

		using dimensions_type = const std::vector<size_type>;

		//Datamember order matters! (for member init list)!
		dimensions_type dimensions_; //const (its in the using which i dont like)

		//Cant be constexpr but all constructors are :(
		const size_type flattened_dims_; //may be too small but want it to be solid on 32 bit machines too

		std::vector<T> values_;


	};

	/////////////////////////////////////////////////////////////////////////////
	//////////////////////// Constructors ///////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	template<typename T>
	constexpr Matrix<T>::Matrix(std::initializer_list<size_type> dimensions, std::initializer_list<T> values)
		: dimensions_(dimensions)
		, flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1, std::multiplies<size_type>()))
		,values_(values)
	{	}

	template<typename T>
	constexpr Matrix<T>::Matrix(std::initializer_list<size_type> dimensions, const T& value)
		: dimensions_(dimensions)
		, flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1, std::multiplies<size_type>()))
		, values_(flattened_dims_, value)
	{}

	template<typename T>
	constexpr Matrix<T>::Matrix(std::initializer_list<size_type> dimensions)
		: dimensions_(dimensions)
		, flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1, std::multiplies<size_type>()))
		, values_(flattened_dims_)
	{}

	//Private:
	template<typename T>
	constexpr Matrix<T>::Matrix(const std::vector<size_type>& dimensions)
		: dimensions_(dimensions)
		, flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1, std::multiplies<size_type>()))
		, values_(flattened_dims_)
	{}

	//Private
	template<typename T>
	constexpr Matrix<T>::Matrix(const std::vector<size_type>& dimensions, const T& value)
		: dimensions_(dimensions)
		, flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1, std::multiplies<size_type>()))
		, values_(flattened_dims_, value)
	{}


	template<typename T>
	constexpr Matrix<T> Matrix<T>::Zeros(std::initializer_list<size_type> dimensions)
	{
		return Matrix(dimensions, (T)0);
	}

	template<typename T>
	template<class InputIt>
	constexpr Matrix<T>::Matrix(std::initializer_list<size_type> dimensions, InputIt first, InputIt last)
		: dimensions_(dimensions)
		, flattened_dims_(std::reduce(dimensions.begin(), dimensions.end(), 1, std::multiplies<size_type>()))
		, values_(first, last)
	{}

	template<typename T>
	constexpr Matrix<T>::Matrix(Matrix&& other)
		: values_(std::move(other.values_))
		, dimensions_(std::move(other.dimensions_))
		, flattened_dims_(std::move(other.flattened_dims_))
	{}

	template<typename T>
	template<typename V>
	constexpr Matrix<T> Matrix<T>::ZerosLike(const Matrix<V>& other)
	{
		return Matrix(other.Shape(), (T)0);
	}

	template<typename T>
	template<typename V>
	constexpr Matrix<T> Matrix<T>::Like(const Matrix<V>& other)
	{
		return Matrix(other.Shape());
	}

	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//////////////////////// Operators //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	template<typename T>
	template<CONSTRAINT(Addable<T>) U>
	Matrix<T>& Matrix<T>::operator+=(const U& scalar)
	{
		//std::for_each is equal in release but I do a lotta debug work so......
		for (typename std::vector<T>::size_type i = 0; i < this->values_.size(); ++i)
		{
			this->values_[i] += scalar;
		}
		return *this;
	}

	template<typename T>
	template<CONSTRAINT(Addable<T>) U>
	Matrix<T>& Matrix<T>::operator+=(const Matrix<U>& rhs)
	{


		for (size_type i = 0; i < this->values_.size(); ++i)
		{
			this->values_[i] += rhs->values_[i];
		}

		return this;
	}

	template<typename T>
	template<CONSTRAINT(Multiplyable<T>) U>
	Matrix<T>& Matrix<T>::operator*=(const U& scalar)
	{
		//std::for_each is equal in release but I do a lotta debug work so......
		for (size_type i = 0; i < this->values_.size(); ++i)
		{
			this->values_[i] *= scalar;
		}
		return *this;
	}

	template<typename T>
	template<CONSTRAINT(Multiplyable<T>) U>
	Matrix<T>& Matrix<T>::operator*=(const Matrix<U>& rhs)
	{
		dimensions_type::size_type dims = this->dimensions_.size();
		dimensions_type::size_type rhs_dims = rhs.dimensions_.size();

		if (dims == rhs_dims)
		{
			if (this->dimensions_ != rhs.dimensions_)
			{
				throw std::domain_error("For Matricies with equal length dimensions \
																 the dimensions must be equal.");
			}
			else
			{
				for (dimensions_type::size_type i = 0; i < this->values_.size(); ++i)
				{
					this->values_[i] *= rhs.values_[i];
				}
			}
		}
		else
		{
			//Order is arbitary as long as the dims are in the same order
			dimensions_type* smaller_matrix_dimensions = &(this->dimensions_);
			dimensions_type* larger_matrix_dimensions = &(rhs.dimensions_);

			Min(smaller_matrix_dimensions, larger_matrix_dimensions, dims, rhs_dims);

			//Now smaller_matrix_dimensions is the smaller of the two;

			dimensions_type::size_type smaller_dims_size = smaller_matrix_dimensions->size();
			dimensions_type::size_type larger_dims_size = larger_matrix_dimensions->size();

			//larger > smaller is garunteed but does auto know this?
			dimensions_type::size_type dim_size_diff = larger_dims_size - smaller_dims_size;

			//dangerous to iterate backwards as vector's sizetype is unsigned 
			//(I now see why)
      //Seems Clang 15's auto doesnt work it out here
			for (dimensions_type::size_type i = 0; i < smaller_dims_size; ++i)
			{
				if (larger_matrix_dimensions[i + dim_size_diff] != smaller_matrix_dimensions[i])
				{
					throw std::domain_error("For Matricies with different length dimensions \
																 the dimensions of the smaller matrix must match the \
																 final dimensions of the longer matrix.");
				}
			}






		}


		return *this;
	}


	/////////////////////////////////////////////////////////////////////////////


} //namespace thoth




#endif

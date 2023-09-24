//#include <cstring>
#include <gtest/gtest.h>

#include <thoth/matrix.h>
#include <stdexcept>

TEST(MatrixBroadcasting, BroadCastFailsOnEqualLengthDifferentDims)
{
	thoth::Matrix<float> m1({ 3,3 }, { 1,2,3,4,5,6,7,8,9 });
	thoth::Matrix<float> m2({ 9 }, { 1,2,3,4,5,6,7,8,9 });

	ASSERT_THROW(m1 *= m2, std::domain_error);

}


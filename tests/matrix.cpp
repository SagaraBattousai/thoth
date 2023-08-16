//#include <cstring>
#include <gtest/gtest.h>

#include <thoth/matrix.h>
#include <stdexcept>

TEST(Min, MinSwaps)
{
	int x = 15;
	int y = 7;
	int *a = &x;
	int *b = &y;

	thoth::Min<>(a, b, x, y); //Shouldn't be visable? annonomous namespace in header so..
	EXPECT_EQ(*a, y);
	EXPECT_EQ(*b, x);
}

TEST(MatrixBroadcasting, BroadCastFailsOnEqualLengthDifferentDims)
{
	thoth::Matrix<float> m1({ 3,3 }, { 1,2,3,4,5,6,7,8,9 });
	thoth::Matrix<float> m2({ 9 }, { 1,2,3,4,5,6,7,8,9 });

	ASSERT_THROW(m1 *= m2, std::domain_error);

}
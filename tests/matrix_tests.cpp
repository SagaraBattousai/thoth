//#include <cstring>
#include <gtest/gtest.h>

#include <thoth/matrix.h>
#include <stdexcept>
#include <initializer_list>

TEST(MatrixBroadcasting, BroadCastFailsOnEqualLengthDifferentDims)
{
	thoth::Matrix<float> m1({ 3,3 }, { 1,2,3,4,5,6,7,8,9 });
	thoth::Matrix<float> m2({ 9 }, { 1,2,3,4,5,6,7,8,9 });

	ASSERT_THROW(m1 *= m2, std::domain_error);

}

TEST(MatrixViews, ViewOf3x3As2x2)
{
	thoth::Matrix<int> mat({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
	thoth::Matrix<int> expected({2, 2}, {5, 6, 8, 9});

	thoth::Matrix<int> actual = mat[{{1, 3}, {1, 3}}];

	EXPECT_EQ((actual[{0, 0}]), (expected[{0, 0}]));
	EXPECT_EQ((actual[{0, 1}]), (expected[{0, 1}]));
	EXPECT_EQ((actual[{1, 0}]), (expected[{1, 0}]));
	EXPECT_EQ((actual[{1, 1}]), (expected[{1, 1}]));
}


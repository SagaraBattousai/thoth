//#include <cstring>
#include <gtest/gtest.h>

#include <thoth/ndarray.h>
#include <stdexcept>
#include <initializer_list>

TEST(NdArrayBroadcasting, BroadCastFailsOnEqualLengthDifferentDims)
{
	thoth::NdArray<float> m1({ 3,3 }, { 1,2,3,4,5,6,7,8,9 });
	thoth::NdArray<float> m2({ 9 }, { 1,2,3,4,5,6,7,8,9 });

	ASSERT_THROW(m1 *= m2, std::domain_error);

}

TEST(NdArrayViews, ViewOf3x3As2x2)
{
	thoth::NdArray<int> mat({3, 3}, {1, 2, 3, 4, 5, 6, 7, 8, 9});
	thoth::NdArray<int> expected({2, 2}, {5, 6, 8, 9});

	thoth::NdArray<int> actual = mat[{{1, 3}, {1, 3}}];

	EXPECT_EQ((actual[{0, 0}]), (expected[{0, 0}]));
	EXPECT_EQ((actual[{0, 1}]), (expected[{0, 1}]));
	EXPECT_EQ((actual[{1, 0}]), (expected[{1, 0}]));
	EXPECT_EQ((actual[{1, 1}]), (expected[{1, 1}]));
}


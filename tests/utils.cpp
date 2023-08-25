//#include <cstring>
#include <gtest/gtest.h>

#include <thoth/utils.h>
#include <stdexcept>

TEST(Min, MinSwaps)
{
	int x = 15;
	int y = 7;
	const int *a = &x;
	const int *b = &y;

	thoth::Min<>(&a, &b, x, y);
	EXPECT_EQ(*a, y);
	EXPECT_EQ(*b, x);
}
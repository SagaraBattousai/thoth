// #include <cstring>
#include <gtest/gtest.h>
#include <thoth/utility.h>

#include <stdexcept>
#include <vector>
#include <functional>

TEST(Min, MinSwaps) {
  int x = 15;
  int y = 7;
  const int *a = &x;
  const int *b = &y;

  thoth::Min<>(&a, &b, x, y);
  EXPECT_EQ(*a, y);
  EXPECT_EQ(*b, x);
}

TEST(ZipWith, MultiplyTwoVectors) { 

  std::vector<int> x{1, 2, 3, 4, 5, 6};
  std::vector<int> y{1, 2, 3, 4, 5, 6};

  std::vector<int> z(x.size());

  std::vector<int> expected{1, 4, 9, 16, 25, 36};

  thoth::ZipWith<int>(x.begin(), x.end(), y.begin(), z.begin(),
                   std::multiplies<int>());

  EXPECT_EQ(z, expected);

}

TEST(ZipWith, MultiplyTwoVectorsWithConvertedType) {
  std::vector<int> x{1, 2, 3, 4, 5, 6};
  std::vector<int> y{1, 2, 3, 4, 5, 6};

  std::vector<float> z(x.size());

  std::vector<float> expected{1.0, 4.0, 9.0, 16.0, 25.0, 36.0};

  thoth::ZipWith<float>(x.begin(), x.end(), y.begin(), z.begin(),
                                std::multiplies<>());

  EXPECT_EQ(z, expected);
}

TEST(ZipWithReduce, MultiplyTwoVectorsAndReduceWithSum) {
  std::vector<int> x{1, 2, 3, 4, 5, 6};
  std::vector<int> y{1, 2, 3, 4, 5, 6};

  float expected = 91; //i.e. Sum{1, 4, 9, 16, 25, 36};

  float z = thoth::ZipWithReduce<>(x.begin(), x.end(), y.begin(), (float)0, std::multiplies<>(), std::plus<>());

  EXPECT_EQ(z, expected);
}
#include <thoth/matrix.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

int main() {
  thoth::Matrix<float> m(
      {2, 2, 3, 4},
      {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
       17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
       34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50});

  thoth::Matrix<float> m2({4},
                          {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
                           13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25});

  std::cout << m2 << "\n\n\n\n" << std::endl;
  std::cout << m << std::endl;

  return 0;
}

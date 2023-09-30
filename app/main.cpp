
#include <memory>
#include <vector>
#include <initializer_list>
#include <numeric>
#include <iostream>
#include <iterator>

#include <thoth/matrix.h>

int main() {
  
  std::vector<thoth::Matrix<float>> vec;
  std::vector<int> strides(1);


  for (int i = (int)strides.size() - 1; i >= 0; --i)
  {
    std::cout << vec[i] << ", " << strides[i] << " : ";
  }

  std::cout << std::endl;

  return 0;
}

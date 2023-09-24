#include <thoth/matrix.h>

#include <memory>
#include <vector>
#include <initializer_list>
#include <iostream>

int main() {
  
  std::shared_ptr<std::vector<int>> ptr = 
    std::make_shared<std::vector<int>>(std::initializer_list{1, 2, 3, 4, 5, 6, 7, 8, 9});

  const int *ptr1 = ptr->data();
  const int *ptr5 = ptr->data() + 5;

  std::cout << (ptr1 == ptr->data()) << ", " << (ptr5 == ptr->data()) << std::endl;

  return 0;
}

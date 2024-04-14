
#include <memory>
#include <vector>
#include <initializer_list>
#include <numeric>
#include <iostream>
#include <iterator>
#include <type_traits>

template <class T>
class X {
 public:
  std::size_t size();

};

template <typename T>
std::size_t X<T>::size() {
  return sizeof(T);
}




int main() {
  
  auto x = X<float>();

  std::cout << x.size() <<  std::endl;

  return 0;
}

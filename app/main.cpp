
#include <iostream>
#include <bitset>
#include <thoth/numeric/bitstring.h>
#include <thoth/utility.h>

int main() {
  
  int a = 7;
  int b = 5;

  const int *x = &a;
  const int *y = &b;

  std::cout << *x << " " << *y << std::endl;
 
  thoth::Min(x, y, a, b);

  std::cout << *x << " " << *y << std::endl;

  return 0;
}

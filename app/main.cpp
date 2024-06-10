
#include <thoth/numeric/bitstring.h>
#include <thoth/numeric/fixed_length_bitstring.h>
#include <thoth/utility.h>

#include <bitset>
#include <concepts>
#include <iostream>
#include <iterator>

using thoth::numeric::BitString;
using thoth::numeric::FixedLengthBitString;

class Foo {
 public:
  using difference_type = std::ptrdiff_t;
  using value_type = int;

  int operator*();
};

int Foo::operator*() { return 7; }

int main() {

  return 0;
}

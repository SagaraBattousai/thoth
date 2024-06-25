
#include <thoth/ml/genetic/crossover.h>
#include <thoth/numeric/bitstring.h>
#include <thoth/numeric/fixed_length_bitstring.h>
#include <thoth/random/random.h>
#include <thoth/utility.h>

#include <bitset>
#include <concepts>
#include <iostream>
#include <iterator>
#include <random>

using thoth::numeric::BitString;
using thoth::numeric::FixedLengthBitString;

int main() {
  auto x = std::uniform_int_distribution(1, 8);
  auto p = x.param();

  return 0;
}


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
  thoth::random::UniformIntegralRNG rng(1, 7);

  double acc = 0;
  const int N = 10;
  int rv;
  for (int i = 0; i < N; ++i) {
    rv = rng();
    acc += rv;
    std::cout << "i : " << i << " => rand = " << rv << std::endl;
  }

  std::cout << "Avg: " << (acc / N) << std::endl;
  std::cout << "EXP: " << (double(1 + 2 + 3 + 4 + 5 + 6 + 7) / 7) << std::endl;

  return 0;
}

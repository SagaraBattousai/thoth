#include <thoth/numeric/fixed_length_bitstring.h>
#include <thoth/tests/numeric/bitstring_tests.h>

namespace thoth {
namespace tests {


template <>
thoth::numeric::BitString*
CreateBitString<thoth::numeric::FixedLengthBitString>(
    std::vector<std::byte> bitstring_value) {
  return new thoth::numeric::FixedLengthBitString(bitstring_value);
}

INSTANTIATE_TYPED_TEST_SUITE_P(FixedBitStringParamatizedTests, BitStringTest,
                               thoth::numeric::FixedLengthBitString);

}
}  // namespace thoth
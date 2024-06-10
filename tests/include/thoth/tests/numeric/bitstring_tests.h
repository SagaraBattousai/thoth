#ifndef __NUMERIC_BITSTRING_TESTS_H__
#define __NUMERIC_BITSTRING_TESTS_H__

#include <gtest/gtest.h>
#include <thoth/numeric/bitstring.h>

#include <cstddef>
#include <vector>

namespace thoth {
namespace tests {

namespace {
constexpr std::byte kOne = std::byte{0x01};
constexpr std::byte kZero = std::byte{0x00};
constexpr std::byte kAllOnes = std::byte{0xFF};

constexpr unsigned char kBitsInByte = 8;
constexpr unsigned char kBigEndianIndexMax = kBitsInByte - 1;

}

// Template factory function to create each concrete bitstring type.
// Ensure specialisation is created before implicit specialisation could
// be instatiated .
// Parameter is byte vector in order to avoid issues with size of primitive
// types (int, long etc)
template <typename T>
thoth::numeric::BitString* CreateBitString(
    std::vector<std::byte> bitstring_value);

// Suite has same name as fixture so dont append "Fixture"
template <typename T>
class BitStringTest : public testing::Test {
 public:
  static const inline std::vector<std::byte> kbitstring_value{
      std::byte{0xDE}, std::byte{0xAD}, std::byte{0xBE},
      std::byte{0xEF}, std::byte{0x37},
  };



 protected:
  BitStringTest();

  ~BitStringTest() override;

  thoth::numeric::BitString* const bitstring_;
};

template <typename T>
BitStringTest<T>::BitStringTest()
    : bitstring_(CreateBitString<T>(kbitstring_value)) {}

template <typename T>
BitStringTest<T>::~BitStringTest() {
  delete bitstring_;
}

// using testing::Types;

TYPED_TEST_SUITE_P(BitStringTest);

TYPED_TEST_P(BitStringTest, LittleEndianBitAccess) {

  for (int j = 0; j < this->kbitstring_value.size(); ++j) {
    for (int i = 0; i < kBitsInByte; ++i) {
      EXPECT_EQ(
          this->bitstring_->GetBit(i + (j * kBitsInByte)),
          ((this->kbitstring_value[j] >> (kBigEndianIndexMax - i)) & kOne));
    }
  }
}

// List test names here
REGISTER_TYPED_TEST_SUITE_P(BitStringTest, LittleEndianBitAccess);

}  // namespace tests
}  // namespace thoth

#endif
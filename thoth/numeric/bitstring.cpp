
#include <thoth/numeric/bitstring.h>

#include <type_traits>

namespace thoth {
namespace numeric {

namespace {
constexpr unsigned char kByteMask = 0xFF;

// Or sizeof(unsigned char for weird arch?
constexpr unsigned char kBitsInByte = 8;
constexpr unsigned char kBigEndianIndexMax = kBitsInByte - 1;

constexpr std::byte kByteOne = std::byte{0x01};

// Since we cant have a template constructor we use this instead.
template <typename T>
void InitBitString(std::vector<std::byte>& bitString, T bits) {
  auto shiftBy = sizeof(T) - 1;
  for (auto i = 0; i < sizeof(T); i++) {
    std::byte currByte = std::byte(bits & (kByteMask << shiftBy));
    bitString.push_back(currByte);
    shiftBy--;
  }
}
}  // namespace

BitString::BitString(int length, Bit initValue)
    : bits_((std::vector<std::byte>::size_type)length, std::byte(initValue)) {}

BitString::BitString(unsigned char bits)
    : bits_((std::vector<std::byte>::size_type) 1, //sizeof(unsigned char),
            std::byte{bits}) {}

BitString::BitString(unsigned int bits)
    : bits_((std::vector<std::byte>::size_type)sizeof(unsigned int)) {
  InitBitString(bits_, bits);
}

BitString::BitString(unsigned long bits)
    : bits_((std::vector<std::byte>::size_type)sizeof(unsigned long)) {
  InitBitString(bits_, bits);
}

BitString::BitString(unsigned long long bits)
    : bits_((std::vector<std::byte>::size_type)sizeof(unsigned long long)) {
  InitBitString(bits_, bits);
}

const BitString::Bit BitString::GetBit(
    std::vector<std::byte>::size_type i) const {
  auto byte_index = i / kBitsInByte; //integer devision
  auto bit_index = kBigEndianIndexMax - (i % kBitsInByte); //BigEndian index

  // Should we call GetByte as it's currently the same but if we change GetByte
  // then should this be the same?
  std::byte byte = bits_[byte_index];

  std::byte bit = (byte >> bit_index) & kByteOne;

  if (bit == kByteOne) {
    return Bit::kOne;
  }

  return Bit::kZero;

}

/*
void BitString::SetBit(std::vector<std::byte>::size_type i, Bit bit) {
  std::byte b = std::byte{(unsigned char) bit};

}
*/

}  // namespace numeric
}  // namespace thoth
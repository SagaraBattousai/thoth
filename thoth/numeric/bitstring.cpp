
#include <thoth/numeric/bitstring.h>
#include <thoth/utility.h>

#include <bitset>
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
  auto shiftBy = (sizeof(T) - 1) * kBitsInByte;
  for (auto i = 0; i < sizeof(T); i++) {
    // bitString[i] = std::byte((bits & (static_cast<T>(kByteMask) << shiftBy))
    // >> shiftBy);
    bitString[i] = std::byte((bits >> shiftBy) & kByteMask);
    // bitString.push_back(currByte);
    shiftBy -= kBitsInByte;
  }
}

}  // namespace

BitString::BitString(int length, Bit initValue)
    : bits_((std::vector<std::byte>::size_type)length, std::byte(initValue)) {}

BitString::BitString(unsigned char bits)
    : bits_((std::vector<std::byte>::size_type)1,  // sizeof(unsigned char),
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

// Private constructor:
BitString::BitString(std::vector<std::byte> bits) : bits_{bits} {}

const BitString::Bit BitString::GetBit(
    std::vector<std::byte>::size_type i) const {
  auto byte_index = i / kBitsInByte;                        // integer devision
  auto bit_index = kBigEndianIndexMax - (i % kBitsInByte);  // BigEndian index

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

std::ostream& operator<<(std::ostream& os, const BitString& obj) {
  auto flags = os.flags();
  os.unsetf(os.showbase);

  if ((flags & os.hex) != 0) {
    os << "0x";
    for (auto i : obj.bits_) {
      unsigned int byte_value = std::to_integer<unsigned int>(i);
      if (byte_value < 0x10) {
        os << 0;
      }
      os << byte_value;
    }
  } else {
    os << "0b";
    for (auto i = 0; i < obj.bits_.size(); i++) {
      os << std::bitset<4>(
                (std::to_integer<unsigned int>(obj.bits_[i]) & 0xF0) >> 4)
         << "_"
         << std::bitset<4>(std::to_integer<unsigned int>(obj.bits_[i]) & 0x0F);
      if (i < obj.bits_.size() - 1) {
        os << " ";
      }
    }
  }

  os.setf(flags, os.showbase);
  return os;
}

// Could inline... but... Should I?
// BitString&
void BitString::Invert() noexcept {
  for (auto& byte : this->bits_) {
    byte = ~byte;
  }
  // return *this;
}

BitString& BitString::ApplyBitwiseArithmetic(
    const BitString& rhs,
    std::function<std::byte(std::byte, std::byte)> f) noexcept {
  const BitString* smaller_bitString = this;
  const BitString* larger_bitString = &rhs;

  Min(smaller_bitString, larger_bitString, smaller_bitString->bits_.size(),
      larger_bitString->bits_.size());

  auto larger_reverse_it = larger_bitString->bits_.crbegin();
  auto smaller_reverse_it = smaller_bitString->bits_.crbegin();
  auto this_reverse_it = this->bits_.rbegin(); //non const

  while (smaller_reverse_it != smaller_bitString->bits_.crend()) {
    *this_reverse_it = f(*larger_reverse_it, *smaller_reverse_it);
    ++larger_reverse_it;
    ++this_reverse_it;
  }

  if (larger_bitString == this) {
    while (this_reverse_it != this->bits_.rend()) {
      *this_reverse_it = f(*this_reverse_it, std::byte{0x00});
      ++this_reverse_it;
    }
  } else {
    auto len_diff = larger_bitString->bits_.size() - this->bits_.size();

  
  }

  return *this;
}

}  // namespace numeric
}  // namespace thoth
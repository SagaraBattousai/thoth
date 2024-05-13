
#include <thoth/numeric/fixed_length_bitstring.h>
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

FixedLengthBitString::FixedLengthBitString(unsigned char bits, int length)
    : bits_((std::vector<std::byte>::size_type)length, std::byte(bits)) {}

FixedLengthBitString::FixedLengthBitString(unsigned int bits, int length)
    : bits_((std::vector<std::byte>::size_type)length) {
  InitBitString(bits_, bits);
}

FixedLengthBitString::FixedLengthBitString(unsigned long bits, int length)
    : bits_((std::vector<std::byte>::size_type)length) {
  InitBitString(bits_, bits);
}

FixedLengthBitString::FixedLengthBitString(unsigned long long bits, int length)
    : bits_((std::vector<std::byte>::size_type)length) {
  InitBitString(bits_, bits);
}

std::byte FixedLengthBitString::GetBit(bits_t::size_type idx) const {
  auto byte_index = idx / kBitsInByte;                        // integer devision
  auto bit_index = kBigEndianIndexMax - (idx % kBitsInByte);  // BigEndian index

  // Should we call GetByte as it's currently the same but if we change GetByte
  // then should this be the same?
  std::byte byte = bits_[byte_index];

  return ((byte >> bit_index) & BitString::kOne);

}

// Returns for modifying not reading therefore must return reference to
//  entire byte. Probably do want SetBit only! TODO:
std::byte& FixedLengthBitString::GetBit(bits_t::size_type idx) {
  auto byte_index = idx / kBitsInByte;  // integer devision
  //auto bit_index = kBigEndianIndexMax - (idx % kBitsInByte);  // BigEndian index

  return bits_[byte_index];
}

std::ostream& FixedLengthBitString::StreamOut(std::ostream& os) const noexcept {
  auto flags = os.flags();
  os.unsetf(os.showbase);

  if ((flags & os.hex) != 0) {
    os << "0x";
    for (auto i : this->bits_) {
      unsigned int byte_value = std::to_integer<unsigned int>(i);
      if (byte_value < 0x10) {
        os << 0;
      }
      os << byte_value;
    }
  } else {
    os << "0b";
    for (auto i = 0; i < this->bits_.size(); i++) {
      os << std::bitset<4>(
                (std::to_integer<unsigned int>(this->bits_[i]) & 0xF0) >> 4)
         << "_"
         << std::bitset<4>(std::to_integer<unsigned int>(this->bits_[i]) & 0x0F);
      if (i < this->bits_.size() - 1) {
        os << " ";
      }
    }
  }

  os.setf(flags, os.showbase);
  return os;
}

void FixedLengthBitString::DoInvert() noexcept {
  for (auto& byte : this->bits_) {
    byte = ~byte;
  }
}

FixedLengthBitString& FixedLengthBitString::ApplyBitwiseArithmetic(
    const BitString& rhs,
    std::function<std::byte(std::byte, std::byte)> f) noexcept {
  //const BitString* smaller_bitString = this;
  //const BitString* larger_bitString = &rhs;

  //Min(smaller_bitString, larger_bitString, smaller_bitString->bits_.size(),
  //    larger_bitString->bits_.size());

  //auto larger_reverse_it = larger_bitString->bits_.crbegin();
  //auto smaller_reverse_it = smaller_bitString->bits_.crbegin();
  //auto this_reverse_it = this->bits_.rbegin(); //non const

  //while (smaller_reverse_it != smaller_bitString->bits_.crend()) {
  //  *this_reverse_it = f(*larger_reverse_it, *smaller_reverse_it);
  //  ++larger_reverse_it;
  //  ++this_reverse_it;
  //}

  //if (larger_bitString == this) {
  //  while (this_reverse_it != this->bits_.rend()) {
  //    *this_reverse_it = f(*this_reverse_it, std::byte{0x00});
  //    ++this_reverse_it;
  //  }
  //} else {
  //  /* auto len_diff = larger_bitString->bits_.size() - this->bits_.size(); */

  //
  //}

  return *this;
}

FixedLengthBitString& FixedLengthBitString::LShift(
  void* shift, std::size_t size_of_shift) noexcept {
  return *this;
}

FixedLengthBitString& FixedLengthBitString::RShift(
  void* shift, std::size_t size_of_shift) noexcept {
  return *this;
}

}  // namespace numeric
}  // namespace thoth


#include <thoth/numeric/fixed_length_bitstring.h>
// #include <thoth/utility.h>

#include <bitset>
#include <type_traits>

namespace thoth {
namespace numeric {

namespace {
constexpr unsigned char kByteMask = 0xFF;

// Or sizeof(unsigned char for weird arch?
constexpr unsigned char kBitsInByte = 8;
constexpr unsigned char kBigEndianIndexMax = kBitsInByte - 1;

// TODO: VV We need length as datamember as non multiple of 8 can cause issues

// Since we cant have a template constructor we use this instead.
template <typename T>
void InitBitString(std::vector<std::byte>& bitString, T bits) {
  // since the size is fixed and we want this code to be nice for embedded.
  bitString.shrink_to_fit();

  // apparently having a variable in both parts of the conditional does not lift
  // its scope

  int startIndex = 0;
  unsigned shiftBy = 0;
  // TODO: handle case when length > bits!
  if (bitString.size() > sizeof(T)) {
    startIndex = (int)(bitString.size() - sizeof(T));
    shiftBy = (sizeof(T) - 1) * kBitsInByte;
  } else {
    shiftBy = (unsigned)((bitString.size() - 1) * kBitsInByte);
  }

  for (int i = startIndex; i < (int) bitString.size(); i++) {
    // bitString[i] = std::byte((bits & (static_cast<T>(kByteMask) << shiftBy))
    // >> shiftBy);
    bitString[i] = std::byte((bits >> shiftBy) & kByteMask);
    // bitString.push_back(currByte);
    shiftBy -= kBitsInByte;
  }
}

}  // namespace

FixedLengthBitString::FixedLengthBitString(unsigned char bits, int length)
    : bits_((std::vector<std::byte>::size_type)length, std::byte(bits)),
      length_{length} {
  bits_.shrink_to_fit();
}

FixedLengthBitString::FixedLengthBitString(unsigned int bits, int length)
    : bits_((std::vector<std::byte>::size_type)length), length_{length} {
  InitBitString(bits_, bits);
}

FixedLengthBitString::FixedLengthBitString(unsigned long bits, int length)
    : bits_((std::vector<std::byte>::size_type)length), length_{length} {
  InitBitString(bits_, bits);
}

FixedLengthBitString::FixedLengthBitString(unsigned long long bits, int length)
    : bits_((std::vector<std::byte>::size_type)length), length_{length} {
  InitBitString(bits_, bits);
}
FixedLengthBitString::FixedLengthBitString(std::vector<std::byte> bitstring)
    : bits_(bitstring), length_{(int) bitstring.size()} {}

  FixedLengthBitString::FixedLengthBitString(std::vector<std::byte> bitstring, int length)
      : bits_(bitstring), length_{length} {}

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
    for (std::vector<std::byte>::size_type i = 0; i < this->bits_.size(); ++i) {
      os << std::bitset<4>(
                (std::to_integer<unsigned int>(this->bits_[i]) & 0xF0) >> 4)
         << "_"
         << std::bitset<4>(std::to_integer<unsigned int>(this->bits_[i]) &
                           0x0F);
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
    std::function<std::byte(const std::byte, const std::byte)> f) noexcept {
  // auto this_iter = this->bits_.rbegin();
  ////auto rhs_iter = rhs.CLittleEndianIter();

  // auto this_end_iter = this->bits_.rend();
  ////auto rhs_end_iter = rhs.CLittleEndianEndIter();

  // BitString::ByteIter& rhs_iter = rhs.

  // while (this_iter != this_end_iter && rhs_iter != rhs_end_iter) {
  //   *this_iter = f(*this_iter, *rhs_iter);
  //   ++this_iter;
  //   ++rhs_iter;
  // }
  ////Cant use size to do rest, check enditers!!
  // if (this_iter != this_end_iter) {
  //   while (this_iter != this_end_iter) {
  //     *this_iter = f(*this_iter, kZero);
  //     ++this_iter;
  //   }
  // }

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

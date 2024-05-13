#ifndef __THOTH_NUMERIC_INFINITE_BITSTRING_H__
#define __THOTH_NUMERIC_INFINITE_BITSTRING_H__

#include <_thoth_config.h>

#ifdef __cplusplus
#include <concepts>
#include <cstddef>
#include <functional>
#include <ostream>
#include <vector>

#include <thoth/numeric/bitstring.h>

namespace thoth {
namespace numeric {

// Maybe not, changing to little endian would be more expensive for shifting if infinate


/**
 * @brief 
 */
class THOTH_EXPORT BitString : public BitString {
 public:
  BitString(int length, unsigned char byte);
  explicit BitString(unsigned char bits);
  explicit BitString(unsigned int bits);
  explicit BitString(unsigned long bits);
  explicit BitString(unsigned long long bits);

  BitString(const BitString&) = default;
  BitString(BitString&&) = default;

  //TODO: Potentially add ability to use private vector<byte> constructor 
  // for little endian and big endian inputs (or promote private constructor)

  // We use this instead of operator[] as it's not possible to get a bit
  // reference and if operator[] returend a byte it wouldn't be so clear
  // since this class is called BitString. However we offer GetByte for
  // conveniance
  const std::byte& GetByte(std::vector<std::byte>::size_type i) const {
    return bits_[i];
  }

  void SetByte(std::vector<std::byte>::size_type i, std::byte byte) {
    bits_[i] = byte;
  }

  // May change belowto be std::byte
  const Bit GetBit(std::vector<std::byte>::size_type i) const;

  void SetBit(std::vector<std::byte>::size_type i, Bit bit);

  // Needs to be a friend but also good to hide from non-ADL lookup
  // (AKA Hiden Friend)
  friend THOTH_EXPORT std::ostream& operator<<(std::ostream&, const BitString&);

  template <std::integral IntegerType>
  BitString& operator<<=(IntegerType shift) noexcept;

  template <std::integral IntegerType>
  BitString& operator>>=(IntegerType shift) noexcept;

  BitString& operator|=(const BitString& rhs) noexcept {
    return this->ApplyBitwiseArithmetic(rhs, std::bit_or<std::byte>{});
  }

  BitString& operator&=(const BitString& rhs) noexcept {
    return this->ApplyBitwiseArithmetic(rhs, std::bit_and<std::byte>{});

  }

  BitString& operator^=(const BitString& rhs) noexcept {
    return this->ApplyBitwiseArithmetic(rhs, std::bit_xor<std::byte>{});
  }

  //BitString& 
  void Invert() noexcept;

  BitString operator~() const noexcept {
    BitString inv(*this);
    inv.Invert();
    return inv;
  }

  // The following are friends so that they are hidden from non-ADL lookup
  // (AKA Hiden Friend)

  friend THOTH_EXPORT BitString operator|(BitString lhs,
                                          const BitString& rhs) noexcept {
    lhs |= rhs;
    return lhs;
  }

  friend THOTH_EXPORT BitString operator&(BitString lhs,
                                          const BitString& rhs) noexcept {
    lhs &= rhs;
    return lhs;
  }

  friend THOTH_EXPORT BitString operator^(BitString lhs,
                                          const BitString& rhs) noexcept {
    lhs ^= rhs;
    return lhs;
  }

  template <std::integral IntegerType>
  friend THOTH_EXPORT constexpr BitString operator<<(
      BitString lhs, IntegerType shift) noexcept {
    lhs <<= shift;
    return lhs;
  }

  template <std::integral IntegerType>
  friend THOTH_EXPORT constexpr BitString operator>>(
      BitString lhs, IntegerType shift) noexcept {
    lhs >>= shift;
    return lhs;
  }

 private:
  BitString(std::vector<std::byte> bits);
  // implementation detail: required here to make the callers inline
  // A template method using decltype and lambda could be cool but would
  // increase
  // code bloat so we'll just pass in a function using std::function
  BitString& ApplyBitwiseArithmetic(
      const BitString& rhs,
      std::function<std::byte(std::byte, std::byte)> f) noexcept;

  std::vector<std::byte> bits_;
};

/************************
 * Non-member functions *
 ************************/

/*******************************
 * Template Method Definitions *
 ******************************/
template <std::integral IntegerType>
BitString& BitString::operator<<=(IntegerType shift) noexcept {
  return *this;
}

template <std::integral IntegerType>
BitString& BitString::operator>>=(IntegerType shift) noexcept {
  return *this;
}
}  // namespace numeric
}  // namespace thoth

#else

#endif

#endif
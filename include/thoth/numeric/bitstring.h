#ifndef __THOTH_NUMERIC_BITSTRING_H__
#define __THOTH_NUMERIC_BITSTRING_H__

#include <_thoth_config.h>

#ifdef __cplusplus
#include <cstddef>
#include <vector>

namespace thoth {
namespace numeric {

// BigEndian
class THOTH_EXPORT BitString {
 public:
  static constexpr int kDefaultBitstringLength = 32;
  enum class Bit : unsigned char { kZero = 0, kOne = 1 };

  static std::byte BitAsByte(Bit bit) {
    return std::byte{static_cast<unsigned char>(bit)};
  }

  /*
  static constexpr Bit ByteAsBit(std::byte byte) {
    if (byte == ) {
    
    }
  }
  */

  explicit BitString(int length = kDefaultBitstringLength,
                     Bit initValue = Bit::kZero);
  explicit BitString(unsigned char bits);
  explicit BitString(unsigned int bits);
  explicit BitString(unsigned long bits);
  explicit BitString(unsigned long long bits);

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

  //May change belowto be std::byte
  const Bit GetBit(std::vector<std::byte>::size_type i) const;

  void SetBit(std::vector<std::byte>::size_type i, Bit bit);


 private:
  std::vector<std::byte> bits_;
};
}  // namespace numeric
}  // namespace thoth

#else

#endif

#endif
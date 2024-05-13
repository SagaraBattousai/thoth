#ifndef __THOTH_NUMERIC_FIXED_LENGTH_BITSTRING_H__
#define __THOTH_NUMERIC_FIXED_LENGTH_BITSTRING_H__

#include <_thoth_config.h>

#ifdef __cplusplus
#include <thoth/numeric/bitstring.h>

#include <concepts>
#include <cstddef>
#include <functional>
#include <ostream>
#include <vector>

namespace thoth {
namespace numeric {

/**
 * @brief
 */

// Actually as theyre all going to be big endian (I've just worked out why
//  and itll only affect infinate BitString we may be able to get
//  datamember in base class!

class THOTH_EXPORT FixedLengthBitString : public BitString {
 public:
  explicit FixedLengthBitString(unsigned char bits, int length);
  explicit FixedLengthBitString(unsigned int bits, int length);
  explicit FixedLengthBitString(unsigned long bits, int length);
  explicit FixedLengthBitString(unsigned long long bits, int length);

  FixedLengthBitString(const FixedLengthBitString&) = default;

  //virtual ~FixedLengthBitString() noexcept override = default;

 private:
  virtual std::byte& GetBit(bits_t::size_type idx) override;
  virtual std::byte GetBit(bits_t::size_type idx) const override;

  virtual std::ostream& StreamOut(std::ostream&) const noexcept override;

  // virtual BitString& ApplyBitwiseArithmetic(
  // Covariant return so change ^ to V
  virtual FixedLengthBitString& ApplyBitwiseArithmetic(
      const BitString& rhs,
      // Check more effective c++ item 33 for this ^^
      std::function<std::byte(std::byte, std::byte)> f) noexcept override;

  // virtual BitString& LShift(
  //   Covariant return so change ^ to V
  virtual FixedLengthBitString& LShift(
      void* shift, std::size_t size_of_shift) noexcept override;

  virtual FixedLengthBitString& RShift(
      void* shift, std::size_t size_of_shift) noexcept override;

  virtual void DoInvert() noexcept override;

  std::vector<std::byte> bits_;
};

}  // namespace numeric
}  // namespace thoth

#else

#endif

#endif
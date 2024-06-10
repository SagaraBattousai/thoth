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
//  datamember in base class! but then its protected so....

class THOTH_EXPORT FixedLengthBitString : public BitString {
 public:
  explicit FixedLengthBitString(unsigned char bits, int length);
  explicit FixedLengthBitString(unsigned int bits, int length);
  explicit FixedLengthBitString(unsigned long bits, int length);
  explicit FixedLengthBitString(unsigned long long bits, int length);

  //TODO: Check this out and check the whole universal ref
  // vs value in modern effective c++
  //Also possibly add one that specifies length
  FixedLengthBitString(std::vector<std::byte> bitstring);
  FixedLengthBitString(std::vector<std::byte> bitstring, int length);

  FixedLengthBitString(const FixedLengthBitString&) = default;

 protected:
   //TODO: Implement after we decide on little or big endian internals!
   virtual std::byte operator[](int idx) const noexcept override {
    return bits_[idx];
  }

   virtual std::byte& operator[](int idx) noexcept override {
    return bits_[idx];
  }

  virtual std::byte DoGetBit(int idx) const noexcept override {
    return BitString::DoGetBit(idx);
  }

  virtual void DoSetBit(int idx) noexcept override { 
    BitString::DoSetBit(idx); 
  }

  virtual void DoClearBit(int idx) noexcept override {
    BitString::DoClearBit(idx);
  }

  virtual void DoFlipBit(int idx) noexcept override {
    BitString::DoFlipBit(idx);
  }

 private:

   virtual int GetLength() const noexcept override { return length_; }

  virtual std::ostream& StreamOut(std::ostream&) const noexcept override;

  // virtual BitString& LShift(
  //   Covariant return so change ^ to V
  virtual FixedLengthBitString& LShift(
      void* shift, std::size_t size_of_shift) noexcept override;

  virtual FixedLengthBitString& RShift(
      void* shift, std::size_t size_of_shift) noexcept override;

  virtual void DoInvert() noexcept override;

  // virtual BitString& ApplyBitwiseArithmetic(
  // Covariant return so change ^ to V
  virtual FixedLengthBitString& ApplyBitwiseArithmetic(
      const BitString& rhs,
      // Check more effective c++ item 33 for this ^^
      std::function<std::byte(const std::byte, const std::byte)> f) noexcept
      override;

  std::vector<std::byte> bits_;
  int length_;

};

}  // namespace numeric
}  // namespace thoth

#else

#endif

#endif
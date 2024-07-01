#ifndef __THOTH_NUMERIC_BITSTRING_H__
#define __THOTH_NUMERIC_BITSTRING_H__

#include <_thoth_config.h>

#ifdef __cplusplus
#include <concepts>
#include <cstddef>
#include <functional>
#include <iterator>
#include <ostream>
#include <ranges>
#include <vector>

namespace thoth {
namespace numeric {

/**
 * @brief Abstract base class of all BitStrings.
 * Decide on Endianness!
 */
class THOTH_EXPORT BitString {

 public:

  static constexpr std::byte kOne = std::byte{0x01};
  static constexpr std::byte kZero = std::byte{0x00};

  static constexpr std::byte kAllOnes = std::byte{0xFF};

  virtual ~BitString() = default;

  // Not called size as this isn't a collecton but rather a type in itself.
  // Originally called NumBits but I thing Length is .... more formal
  int Length() const noexcept { return GetLength(); }

  std::byte GetBit(int idx) const noexcept { return DoGetBit(idx); }

  bool CheckBit(int idx) const noexcept { return kOne == DoGetBit(idx); }
  
  void SetBit(int idx) noexcept { DoSetBit(idx); }

  void ClearBit(int idx) noexcept { DoClearBit(idx); }

  void FlipBit(int idx) noexcept { DoFlipBit(idx); }

  void Invert() noexcept { DoInvert(); }

  template <std::integral IntegerType>
  BitString& operator<<=(IntegerType shift) noexcept {
    return LShift(&shift, sizeof(shift));
  }

  template <std::integral IntegerType>
  BitString& operator>>=(IntegerType shift) noexcept {
    return RShift(&shift, sizeof(shift));
  }

  BitString& operator|=(const BitString& rhs) noexcept {
    return ApplyBitwiseArithmetic(rhs, std::bit_or<const std::byte>{});
  }

  BitString& operator&=(const BitString& rhs) noexcept {
    return ApplyBitwiseArithmetic(rhs, std::bit_and<const std::byte>{});
  }

  BitString& operator^=(const BitString& rhs) noexcept {
    return ApplyBitwiseArithmetic(rhs, std::bit_xor<const std::byte>{});
  }

  // Needs to be a friend but also good to hide from non-ADL lookup
  // (AKA Hiden Friend)
  friend THOTH_EXPORT std::ostream& operator<<(std::ostream& os,
                                               const BitString& bs) noexcept {
    return bs.StreamOut(os);
  }

  // Can no longer do friend binary (non-assignment) operators as they
  //  return by value. Unless we want to return by unique_ptr which
  //  is .... inelegant.
  //
  // Or can we! Templates !?! Are templates already hidden from non-ADL lookup?

  // Could we pass by value??
  template <typename T, typename U>
    requires std::derived_from<T, BitString> && std::derived_from<U, BitString>
  friend T operator|(const T& lhs, const T& rhs) noexcept {
    return T(lhs) |= rhs;
    // lhs.DoBinaryBitwise(rhs, std::bit_or<std::byte>{})
  }

  template <typename T, typename U>
    requires std::derived_from<T, BitString> && std::derived_from<U, BitString>
  friend T operator&(const T& lhs, const T& rhs) noexcept {
    return T(lhs) &= rhs;
  }

  template <typename T, typename U>
    requires std::derived_from<T, BitString> && std::derived_from<U, BitString>
  friend T operator^(const T& lhs, const T& rhs) noexcept {
    return T(lhs) ^= rhs;
  }

  template <typename T>
    requires std::derived_from<T, BitString>
  T operator~() const noexcept {
    // Check that this == derived
    /*T inv(*this);
    inv.Invert();
    return inv;*/
    return T(*this).Invert();
  }

  template <typename T, std::integral IntegerType>
    requires std::derived_from<T, BitString>
  friend THOTH_EXPORT constexpr T operator<<(const T& lhs,
                                             IntegerType shift) noexcept {
    /*lhs <<= shift;
    return lhs;*/
    return T(lhs) <<= shift;
  }

  template <typename T, std::integral IntegerType>
    requires std::derived_from<T, BitString>
  friend THOTH_EXPORT constexpr T operator>>(
      const T& lhs, IntegerType shift) noexcept {
    /*lhs >>= shift;
    return lhs;*/
    return T(lhs) >>= shift;
  }

 protected:
  // BitString(const BitString&) = default;

  // Must be big endian access
  virtual std::byte operator[](int idx) const noexcept = 0;

  virtual std::byte& operator[](int idx) noexcept = 0;

  /////////////////////////////////////////////////////////////////////////////
  // The following functions have a default implementation (hence protected
  //  instead of private) but are pure so that the implementor must explicitly
  //  state if they want to use the default implemntation.
  // 
  // Or what if I made these non-virtual and made the pure version private?
  // But then there would be a third name (but it would just be called DefaultXyz
  // 
  /////////////////////////////////////////////////////////////////////////////
  virtual std::byte DoGetBit(int idx) const noexcept = 0;

  virtual void DoSetBit(int idx) noexcept = 0;

  virtual void DoClearBit(int idx) noexcept = 0;

  virtual void DoFlipBit(int idx) noexcept = 0;

  //////////////////////////////////////////////////////////////////

 private:

  virtual int GetLength() const noexcept = 0;

  virtual std::ostream& StreamOut(std::ostream&) const noexcept = 0;

  virtual BitString& LShift(void* shift,
                            std::size_t size_of_shift) noexcept = 0;

  virtual BitString& RShift(void* shift,
                            std::size_t size_of_shift) noexcept = 0;

  virtual void DoInvert() noexcept = 0;

  virtual BitString& ApplyBitwiseArithmetic(
      const BitString& rhs,
      std::function<std::byte(const std::byte, const std::byte)>
          f) noexcept = 0;

  // virtual std::ranges::iterator_t<std::byte> GetLittleEndianIter() = 0;
};

}  // namespace numeric
}  // namespace thoth

#else

#endif

#endif

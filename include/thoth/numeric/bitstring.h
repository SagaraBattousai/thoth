#ifndef __THOTH_NUMERIC_BITSTRING_H__
#define __THOTH_NUMERIC_BITSTRING_H__

#include <_thoth_config.h>

#ifdef __cplusplus
#include <concepts>
#include <cstddef>
#include <functional>
#include <ostream>
#include <vector>

namespace thoth {
namespace numeric {

/**
 * @brief Abstract base class of all BitStrings
 */
class THOTH_EXPORT BitString {
 protected:
  // protected alias'
  using bits_t = std::vector<std::byte>;
  static constexpr std::byte kOne = std::byte{0x01};

 public:
  virtual ~BitString() = default;// = 0;

  std::byte operator[](bits_t::size_type idx) const {
    return GetBit(idx);
  }

  // only for writing ?
  std::byte& operator[](bits_t::size_type idx) { return GetBit(idx); }

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
    return ApplyBitwiseArithmetic(rhs, std::bit_or<std::byte>{});
  }

  BitString& operator&=(const BitString& rhs) noexcept {
    return ApplyBitwiseArithmetic(rhs, std::bit_and<std::byte>{});
  }

  BitString& operator^=(const BitString& rhs) noexcept {
    return ApplyBitwiseArithmetic(rhs, std::bit_xor<std::byte>{});
  }

  // Needs to be a friend but also good to hide from non-ADL lookup
  // (AKA Hiden Friend)
  friend THOTH_EXPORT std::ostream& operator<<(std::ostream& os,
                                               const BitString& bs) {
    return bs.StreamOut(os);
  }

  // Can no longer do friend binary (non-assignment) operators as they
  //  return by value. Unless we want to return by unique_ptr which
  //  is .... inelegant.
  //
  // Or can we! Templates !?! Are templates already hidden from non-ADL lookup?

  //Could we pass by value??
  template <typename T>
    requires std::derived_from<T, BitString>
  friend T operator|(const T& lhs, const T& rhs) noexcept {
    return T(lhs) |= rhs;
      //lhs.DoBinaryBitwise(rhs, std::bit_or<std::byte>{})
  }

  template <typename T>
    requires std::derived_from<T, BitString>
  friend T operator&(const T& lhs, const T& rhs) noexcept {
    return T(lhs) &= rhs;
  }

  template <typename T>
    requires std::derived_from<T, BitString>
  friend T operator^(const T& lhs, const T& rhs) noexcept {
    return T(lhs) ^= rhs;
  }

   template <typename T>
    requires std::derived_from<T, BitString>
   T operator~() const noexcept {
     //Check that this == derived
    /*T inv(*this);
    inv.Invert();
    return inv;*/
     return T(*this).Invert();
  }

  template <typename T, std::integral IntegerType>
    requires std::derived_from<T, BitString>
  friend THOTH_EXPORT constexpr T operator<<(
      const T& lhs, IntegerType shift) noexcept {
    /*lhs <<= shift;
    return lhs;*/
    return T(lhs) <<= shift;
  }

  template <typename T, std::integral IntegerType>
    requires std::derived_from<T, BitString>
  friend THOTH_EXPORT constexpr BitString operator>>(
      const T& lhs, IntegerType shift) noexcept {
    /*lhs >>= shift;
    return lhs;*/
    return T(lhs) >>= shift;
  }

  protected:
  //BitString(const BitString&) = default;


 private:
   //only for writing ?
  virtual std::byte& GetBit(bits_t::size_type idx) = 0;
  virtual std::byte GetBit(bits_t::size_type idx) const = 0;

  virtual std::ostream& StreamOut(std::ostream&) const noexcept = 0;

  virtual BitString& LShift(void* shift,
                            std::size_t size_of_shift) noexcept = 0;

  virtual BitString& RShift(void* shift,
                            std::size_t size_of_shift) noexcept = 0;

  virtual void DoInvert() noexcept = 0;

  virtual BitString& ApplyBitwiseArithmetic(
      const BitString& rhs,
      std::function<std::byte(std::byte, std::byte)> f) noexcept = 0;
};

/************************
 * Non-member functions *
 ************************/

/*******************************
 * Template Method Definitions *
 ******************************/
//template <std::integral IntegerType>
//BitString& BitString::operator<<=(IntegerType shift) noexcept {
//  return *this;
//}
//
//template <std::integral IntegerType>
//BitString& BitString::operator>>=(IntegerType shift) noexcept {
//  return *this;
//}
}  // namespace numeric
}  // namespace thoth

#else

#endif

#endif
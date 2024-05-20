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
 * @brief Abstract base class of all BitStrings.
 * Decide on Endianness!
 */
class THOTH_EXPORT BitString {
 protected:
  // protected alias'

  // Is this forcing us to use vector? should this change? What about Iters?
  //  How do we say any iter that returns std::byte
  using bits_t = std::vector<std::byte>;
  static constexpr std::byte kOne = std::byte{0x01};
  static constexpr std::byte kZero = std::byte{0x00};

 public:
  virtual ~BitString() = default;

  std::byte operator[](bits_t::size_type idx) const { return GetBit(idx); }

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
                                               const BitString& bs) {
    return bs.StreamOut(os);
  }

  // Can no longer do friend binary (non-assignment) operators as they
  //  return by value. Unless we want to return by unique_ptr which
  //  is .... inelegant.
  //
  // Or can we! Templates !?! Are templates already hidden from non-ADL lookup?

  // Could we pass by value??
  template <typename T>
    requires std::derived_from<T, BitString>
  friend T operator|(const T& lhs, const T& rhs) noexcept {
    return T(lhs) |= rhs;
    // lhs.DoBinaryBitwise(rhs, std::bit_or<std::byte>{})
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
  friend THOTH_EXPORT constexpr BitString operator>>(
      const T& lhs, IntegerType shift) noexcept {
    /*lhs >>= shift;
    return lhs;*/
    return T(lhs) >>= shift;
  }
  
 protected:
  // BitString(const BitString&) = default;

  // For now: This will be a Forward Iter as this is all we need even though
  // Anyone using Array, vector etc will have a contiguous iterator for free.
  // Actually now this is protected its safe to leave as Forward but maybe
  // BitIter will require a change?
  // This may allow us to lift more code into here
  //
  // Different attempt now!

  // template <typename It>
  // class BitStringByteIter {
  // public:
  //  using difference_type = std::ptrdiff_t;
  //  using value_type = std::byte;
  //  using iterator_concept = std::forward_iterator_tag;

  //  value_type operator*() const { return Deref(); };
  //  It& operator++() { return PrefixInc(); }

  //  It operator++(int) {
  //    //auto tmp = *this;
  //    ++*this;
  //    //return tmp;
  //  }

  //  bool operator==(const BitStringByteIter& rhs) const {
  //    return DoEquality(rhs);
  //  }

  // private:
  //  virtual value_type Deref() const = 0;
  //  virtual It& PrefixInc() = 0;
  //  virtual bool DoEquality(const BitStringByteIter& rhs) const = 0;
  //};

  // Final attempt //Maybe make more c++y later
  class THOTH_EXPORT ByteIter {
   public:
    bool HasNext() const { return DoHasNext(); }
    std::byte& operator*() const { return Deref(); };
    void Next() { DoNext(); };

   private:
    virtual bool DoHasNext() const = 0;
    virtual std::byte& Deref() const = 0;
    virtual void DoNext() = 0;
  };

  ByteIter& LittleEndianIter() { return GetLittleEndianIter(); };

 private:
  // only for writing ?
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
      std::function<std::byte(const std::byte, const std::byte)>
          f) noexcept = 0;

  virtual ByteIter& GetLittleEndianIter() = 0;
};

}  // namespace numeric
}  // namespace thoth

#else

#endif

#endif
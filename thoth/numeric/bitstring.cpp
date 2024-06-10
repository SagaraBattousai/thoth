
#include <thoth/numeric/bitstring.h>

namespace thoth {
namespace numeric {

namespace {

constexpr unsigned char kByteMask = 0xFF;

// Or sizeof(unsigned char for weird arch?
constexpr unsigned char kBitsInByte = 8;
constexpr unsigned char kBigEndianIndexMax = kBitsInByte - 1;

// Was going to use pair but pointer is cool 
// (though is pointer larger than int)
inline void splitBigEndianIndex(int idx, int *const byte_index, int *const bit_shift) {
  *byte_index = idx / kBitsInByte;  // integer devision
  *bit_shift = kBigEndianIndexMax - (idx % kBitsInByte);
}

}

std::byte BitString::DoGetBit(int idx) const noexcept {
  int byte_index;
  int bit_shift;
  splitBigEndianIndex(idx, &byte_index, &bit_shift);

  return kOne & (this->operator[](byte_index) >> bit_shift);
}

void BitString::DoSetBit(int idx) noexcept {
  int byte_index;
  int bit_shift;
  splitBigEndianIndex(idx, &byte_index, &bit_shift);

  // I hope this uses write version i.e return bit&
  this->operator[](byte_index) |= (kOne << bit_shift);

}

void BitString::DoClearBit(int idx) noexcept {
  int byte_index;
  int bit_shift;
  splitBigEndianIndex(idx, &byte_index, &bit_shift);

  // I hope this uses write version i.e return bit&
  this->operator[](byte_index) &= ((kOne << bit_shift) ^ kAllOnes);
}

//
// Since this is the same as DoSetBit except with the xor instead of or perhaps
// we should extract?
//
void BitString::DoFlipBit(int idx) noexcept {
  int byte_index;
  int bit_shift;
  splitBigEndianIndex(idx, &byte_index, &bit_shift);

  // I hope this uses write version i.e return bit&
  this->operator[](byte_index) ^= (kOne << bit_shift);
}


}  // namespace numeric
}  // namespace thoth

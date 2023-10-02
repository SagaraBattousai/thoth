#ifndef __THOTH_CRYPTO_KECCAK_H__
#define __THOTH_CRYPTO_KECCAK_H__

#include <_thoth_config.h>

#ifdef __cplusplus
#include <cstdint>

#include <thoth/hash.h>

namespace thoth
{
	THOTH_EXPORT hash_output Keccak224(hash_input);

	THOTH_EXPORT hash_output Keccak256(hash_input);

	THOTH_EXPORT hash_output Keccak384(hash_input);

	THOTH_EXPORT hash_output Keccak512(hash_input);
}
extern "C" {
#else
#include <stdint.h>
#endif

THOTH_EXPORT void keccak224(const uint8_t *input, int byteCount, uint8_t *output);
	
THOTH_EXPORT void keccak256(const uint8_t *input, int byteCount, uint8_t *output);
	
THOTH_EXPORT void keccak384(const uint8_t *input, int byteCount, uint8_t *output);

THOTH_EXPORT void keccak512(const uint8_t *input, int byteCount, uint8_t *output);

#ifdef __cplusplus
}
#endif


#endif

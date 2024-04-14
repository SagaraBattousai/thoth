#ifndef __THOTH_ML_GENETIC_CROSSOVER_H_
#define __THOTH_ML_GENETIC_CROSSOVER_H_

#include <_thoth_config.h>

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif  // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

THOTH_EXPORT void SingleCrossover(const void *g1, const void *g2, void *dst,
                                         std::size_t pointer_size, std::size_t pointer_length);






#ifdef __cplusplus
}
#endif  // __cplusplus

#endif
#ifndef __THOTH_ML_GENETIC_PTR_GENE_BASE_H__
#define __THOTH_ML_GENETIC_PTR_GENE_BASE_H__
/**@file */

#include <_thoth_config.h>

#ifdef __cplusplus
#include <functional>
#include <utility>
#endif
#include <thoth/ml/genetic/gene.h>

#include <cstddef>

#ifdef __cplusplus
namespace thoth {
namespace ml {
// TODO: Should we change all void* to unsigned char* ????
//
// Could remove export in order to stop anyone directly using this.
// Do we want to access this directly from C / Python?
// Does not inherit Gene as this is just an implementation detail for the
// Template classes.
class THOTH_EXPORT PtrGeneBase {
 public:
  // For now we'll use function class for strategy instead of a separate class
  // hierarchy: A) It's more flexible and B) We don't need a hierarchy that
  // mirrors gene (although we could)
  using CrossoverFunc = std::function<void(const void*, const void*, void*,
                                           std::size_t, std::size_t)>;
  using MutationFunc = std::function<void(void*, std::size_t, std::size_t)>;

  PtrGeneBase(void*, std::size_t, std::size_t, CrossoverFunc, MutationFunc);

  // Could be inlined? If in doubt ... no?
  void Mutate();

  // Could be inlined? If in doubt ... no?
  void Crossover(const void* other, void* dst) const;

 private:
  // const void* const GetDNA() const { return data_; }

  void* data_;  // Could be ref? since data_must exist elsewhere
  std::size_t data_type_size_;
  std::size_t data_length_;
  CrossoverFunc crossover_func_;
  MutationFunc mutation_func_;
};
}  // namespace ml
}  // namespace thoth

#endif

#endif

#ifndef __THOTH_ML_GENETIC_PTR_GENE_H__
#define __THOTH_ML_GENETIC_PTR_GENE_H__
/**@file */
/*

#include <_thoth_config.h>

#ifdef __cplusplus

#include <utility>

namespace thoth {
namespace ml {
template <typename T>
class THOTH_EXPORT PtrGene {
 public:
  using gene_t = const Gene* const;
  // NOTE: May stop it being immutable as copying data
  // could be expensive but there may be a way...?
  virtual gene_t mutate() const = 0;

  // TODO: Should this be friends as they x.f(y) == y.f(x)
  //Can be single crossover, dual crossover, uniform crossover etc. up to the
  // implementor
    
  virtual std::pair<gene_t, gene_t> crossover(gene_t other) = 0;
};
}  // namespace ml
}  // namespace thoth

#endif
*/
#endif
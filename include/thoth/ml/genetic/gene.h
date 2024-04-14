#ifndef __THOTH_ML_GENETIC_GENE_H__
#define __THOTH_ML_GENETIC_GENE_H__
/**@file */

#include <_thoth_config.h>

#ifdef __cplusplus

#include <utility>

namespace thoth {
namespace ml {
class THOTH_EXPORT Gene {
 public:
   using gene_ptr = const Gene* const;
   //NOTE: May stop it being immutable as copying data
   //could be expensive but there may be a way...?
  virtual gene_ptr mutate() const = 0;

  //TODO: Should this be friends as they x.f(y) == y.f(x)
  /**Can be single crossover, dual crossover, uniform crossover etc. up to the implementor */
  virtual std::pair<gene_ptr, gene_ptr> crossover(gene_ptr other) = 0;



};
}  // namespace ml
}  // namespace thoth

#endif

#endif
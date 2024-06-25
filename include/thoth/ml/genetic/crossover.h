#ifndef __THOTH_ML_GENETIC_CROSSOVER_H_
#define __THOTH_ML_GENETIC_CROSSOVER_H_

// #include <_thoth_config.h>

#ifdef __cplusplus
// #include <cstddef>

#include <thoth/concepts.h>
#include <thoth/ml/genetic/gene_base.h>

#include <random>
#include <utility>

namespace thoth {

//TODO: Learn Ranges and views when you have time (which will be a while)

// Note, I originally did not like splitting it up into smaller multiple classes
// but since templates are only made if used, its quite good, I think?

template <typename Derived, typename Gene>
class SinglePointCrossover {
 public:
  void Crossover(const Gene& parent1, const Gene& parent2, Gene* const child1,
                 Gene* const child2) const {
    int gene_length = parent1.length;
    // Force int as subclass can decide how to cast/convert.
    //  Additionally it keeps interface uniform
    int point =
        static_cast<Derived*>(this)->GetCrossoverPoint(0, gene_length - 1);

    auto p1_it = parent1.cbegin();
    auto p2_it = parent2.cbegin();
    auto c1_it = child1->begin();
    auto c2_it = child2->begin();

    //Would this be nicer as a single while loop?
    for (int i = 0; i < point; ++i) {
      *c1_it = *p1_it;
      *c2_it = *p2_it;
    }
    for (int i = point; i < gene_length; ++i) {
      *c1_it = *p2_it;
      *c2_it = *p1_it;
    }

  }

 private:
  // I originally didn't like the look of this but as (for this class)
  // we cannot guarantee that Derived will have an empty/default constructor
  // and the friendness protects against incorrect crtp usage.
  friend Derived;
  SinglePointCrossover() = default;
};

}  // namespace thoth
#endif  // __cplusplus
#endif

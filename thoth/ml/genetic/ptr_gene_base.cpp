
#include <thoth/ml/genetic/ptr_gene_base.h>

namespace thoth {
namespace ml {

PtrGeneBase::PtrGeneBase(void* data, std::size_t data_type_size,
                         std::size_t data_length, CrossoverFunc crossover_func,
                         MutationFunc mutation_func)
    : data_(data),
      data_type_size_(data_type_size),
      data_length_(data_length),
      crossover_func_(crossover_func),
      mutation_func_(mutation_func) {}


void PtrGeneBase::Mutate() {
  this->mutation_func_(data_, data_type_size_, data_length_);
}

void PtrGeneBase::Crossover(const void* other, void* dst) const {
  this->crossover_func_(data_, other, dst, data_type_size_, data_length_);
}

}  // namespace ml
}  // namespace thoth
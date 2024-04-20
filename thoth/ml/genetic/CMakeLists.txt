
set(GENETIC_MODULE_ROOT "${MODULE_ROOT}/thoth/ml/genetic")

set(cpp_sources
  "ptr_gene_base.cpp"
  "crossover.cpp"
  "mutation.cpp"
  )

set(c_sources "")

set(genetic_module 
  "${GENETIC_MODULE_ROOT}/gene.h"
  "${GENETIC_MODULE_ROOT}/ptr_gene_base.h"
  "${GENETIC_MODULE_ROOT}/ptr_gene.h"
  "${GENETIC_MODULE_ROOT}/vector_gene.h"
  "${GENETIC_MODULE_ROOT}/crossover.h"
  "${GENETIC_MODULE_ROOT}/mutation.h"
  )

add_library(genetic SHARED ${cpp_sources} ${c_sources})

# Could be private but I think the clients should have access to bitstring class too
target_link_libraries(genetic PUBLIC numeric) 

target_sources(genetic PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES "${MODULE_ROOT}/_thoth_config.h" "${genetic_module}"
  )

if(WIN32)
  target_compile_definitions(genetic PRIVATE THOTH_BUILD_DLL)
endif()

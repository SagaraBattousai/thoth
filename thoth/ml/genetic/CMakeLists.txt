
set(GENETIC_MODULE_ROOT "${MODULE_ROOT}/thoth/ml/genetic")

set(cpp_sources
  "gene.cpp"
  )

set(c_sources "")

set(genetic_module 
  "${GENETIC_MODULE_ROOT}/gene.h"
  )

add_library(genetic SHARED ${cpp_sources} ${c_sources})

target_sources(genetic PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES "${MODULE_ROOT}/_thoth_config.h" "${genetic_module}"
  )

if(WIN32)
  target_compile_definitions(genetic PRIVATE THOTH_BUILD_DLL)
endif()

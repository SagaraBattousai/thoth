
set(concepts_module
  "${MODULE_ROOT}/thoth/concepts.h"
  )

add_library(concepts INTERFACE)

target_sources(concepts PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${concepts_module}
  )

target_compile_features(concepts INTERFACE cxx_std_20)

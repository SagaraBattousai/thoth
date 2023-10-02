
set(CONCEPTS_MODULE_ROOT "${MODULE_ROOT}/thoth/concepts")

set(concepts_module
  "${CONCEPTS_MODULE_ROOT}/thoth/concepts.h"
  )

add_library(concepts INTERFACE)

target_sources(concepts PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${CONCEPTS_MODULE_ROOT}
  FILES ${concepts_module}
  )

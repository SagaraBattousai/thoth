
set(UTILITY_MODULE_ROOT "${MODULE_ROOT}/thoth/utility")

set(utility_module
  "${UTILITY_MODULE_ROOT}/thoth/utility.h"
  )

add_library(utility INTERFACE)# ${utility_module})

target_sources(utility PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${UTILITY_MODULE_ROOT}
  FILES ${utility_module}
  )

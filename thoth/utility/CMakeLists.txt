
set(utility_module
  "${MODULE_ROOT}/thoth/concepts.h"
  "${MODULE_ROOT}/thoth/enum_flag.h"
  "${MODULE_ROOT}/thoth/utility.h"
  )

add_library(utility INTERFACE)

target_sources(utility PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${utility_module}
  )

target_compile_features(utility INTERFACE cxx_std_20)


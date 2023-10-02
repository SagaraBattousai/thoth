
set(NUMERIC_MODULE_ROOT "${MODULE_ROOT}/thoth/numeric")


set(cpp_sources 
  # "bigint.cpp"
  "integral.cpp"
  # "core_integral.cpp"
  )

set(c_sources "")

set(numeric_module 
  "${NUMERIC_MODULE_ROOT}/thoth/integral.h"
  #"${NUMERIC_MODULE_ROOT}/thoth/core-integral.h"
  )

add_library(numeric SHARED ${cpp_sources} ${c_sources})

target_compile_definitions(numeric PRIVATE THOTH_BUILD_DLL)

target_sources(numeric PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${NUMERIC_MODULE_ROOT}
  FILES ${numeric_module}
  )

target_sources(numeric PUBLIC
  FILE_SET config_headers
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES "${MODULE_ROOT}/_thoth_config.h"
  )


#TODO: Check how private works with install
target_link_libraries(numeric PUBLIC utility)

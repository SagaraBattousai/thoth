
set(THOTH_MODULE_ROOT "${MODULE_ROOT}/thoth")

set(cpp_sources "matrix_base.cpp" "square_matrix_base.cpp")
set(c_sources "")
set(thoth_module
  "${THOTH_MODULE_ROOT}/matrix.h"
  "${THOTH_MODULE_ROOT}/square_matrix.h"
  )

if(MSVC)
  list(APPEND cpp_sources "cpp.hint")
endif()

add_library(thoth SHARED ${cpp_sources} ${c_sources})

target_compile_definitions(thoth PRIVATE THOTH_BUILD_DLL)

target_sources(thoth PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${thoth_module}
  "${MODULE_ROOT}/_thoth_config.h" # Probably should be private although ...
  )




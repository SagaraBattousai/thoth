
set(NDARRAY_MODULE_ROOT "${MODULE_ROOT}/thoth/ndarray")

set(cpp_sources "ndarray_simd.cpp")
set(c_sources "")
set(ndarray_module
  "${NDARRAY_MODULE_ROOT}/thoth/ndarray.h"
  #"${NDARRAY_MODULE_ROOT}/thoth/ndarray_simd.h"
  )

add_library(ndarray INTERFACE) #SHARED ${cpp_sources} ${c_sources})

# target_compile_definitions(ndarray PRIVATE THOTH_BUILD_DLL)

target_sources(ndarray PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${NDARRAY_MODULE_ROOT}
  FILES ${ndarray_module}
  )

target_sources(ndarray PUBLIC
  FILE_SET config_headers
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES "${MODULE_ROOT}/_thoth_config.h"
  )

#TODO: Check how private works with install
target_link_libraries(ndarray INTERFACE concepts utility)

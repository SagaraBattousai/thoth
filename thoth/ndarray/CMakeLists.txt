
set(NDARRAY_MODULE_ROOT "${MODULE_ROOT}/thoth/ndarray")

set(cpp_sources "ndarray_simd.cpp")
set(c_sources "")
set(ndarray_module
  "${NDARRAY_MODULE_ROOT}/ndarray.h"
  #"${NDARRAY_MODULE_ROOT}/ndarray_simd.h"
  )

add_library(ndarray INTERFACE) #SHARED ${cpp_sources} ${c_sources})

# target_compile_definitions(ndarray PRIVATE THOTH_BUILD_DLL)

target_sources(ndarray PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${ndarray_module}
  "${MODULE_ROOT}/_thoth_config.h" # even this isnt right?
  )

# TODO: Check how all this works as msvc is claiming it can't
# see project includes

target_link_libraries(ndarray INTERFACE concepts utility)

target_compile_features(ndarray INTERFACE cxx_std_20)

get_target_property(ph ndarray PUBLIC_HEADER)
message(STATUS "ph = ${ph}")

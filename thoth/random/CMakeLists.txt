
set(RANDOM_MODULE_ROOT "${MODULE_ROOT}/thoth/random")


set(cpp_sources 
  "random.cpp"
  )

set(c_sources "")

set(random_module 
  "${RANDOM_MODULE_ROOT}/random.h"
  )

add_library(random SHARED ${cpp_sources} ${c_sources})

target_compile_definitions(random PRIVATE THOTH_BUILD_DLL)

target_sources(random PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${random_module}
  "${MODULE_ROOT}/_thoth_config.h"
  )


##TODO: Check how private works with install
#target_link_libraries(random PUBLIC utility)

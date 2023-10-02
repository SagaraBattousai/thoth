
set(NETWORK_MODULE_ROOT "${MODULE_ROOT}/thoth/network")

set(cpp_sources "network.cpp" "network_unix.cpp" "network_win32.cpp")
set(c_sources "")
set(network_module
  "${NETWORK_MODULE_ROOT}/thoth/network.h"
  "${NETWORK_MODULE_ROOT}/thoth/network_unix.h"
  "${NETWORK_MODULE_ROOT}/thoth/network_win32.h"
  )

add_library(network SHARED ${cpp_sources} ${c_sources})

target_compile_definitions(network PRIVATE THOTH_BUILD_DLL)

target_sources(network PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${NETWORK_MODULE_ROOT}
  FILES ${network_module}
  )


target_sources(network PUBLIC
  FILE_SET config_headers
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES "${MODULE_ROOT}/_thoth_config.h"
  )

if(MSVC)
  target_link_libraries(network PRIVATE Ws2_32)
endif()

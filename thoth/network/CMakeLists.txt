set(NETWORK_MODULE_ROOT "${MODULE_ROOT}/thoth/network")

# NOTE: Just cleaner to write it all out than use list(TRANSFORM ...) and 3 vars

set(cpp_sources
    "network.cpp"
    "socket.cpp"
    "p2p.cpp"
    #Win32 Sources
    "win32/network_win32.cpp"
    "win32/socket_win32.cpp"
    "win32/p2p_win32.cpp"
    #Unix Sources
    "unix/network_unix.cpp"
    "unix/socket_unix.cpp"
    "unix/p2p_unix.cpp")

set(c_sources "")

set(network_module
    "${NETWORK_MODULE_ROOT}/network.h" 
    "${NETWORK_MODULE_ROOT}/socket.h"
    "${NETWORK_MODULE_ROOT}/p2p.h"
    #Win32 Headers
    "${NETWORK_MODULE_ROOT}/internal/win32/network_win32.h"
    "${NETWORK_MODULE_ROOT}/internal/win32/socket_win32.h"
    "${NETWORK_MODULE_ROOT}/internal/win32/p2p_win32.h"
    #Unix Headers
    "${NETWORK_MODULE_ROOT}/internal/unix/network_unix.h" 
    "${NETWORK_MODULE_ROOT}/internal/unix/socket_unix.h" 
    "${NETWORK_MODULE_ROOT}/internal/unix/p2p_unix.h")

add_library(network SHARED ${cpp_sources} ${c_sources})

target_sources(
  network
  PUBLIC FILE_SET
         HEADERS
         TYPE
         HEADERS
         BASE_DIRS
         ${MODULE_ROOT}
         FILES
         ${network_module}
         "${MODULE_ROOT}/_thoth_config.h")

if(MSVC)
  target_link_libraries(network PRIVATE Ws2_32)
  target_compile_definitions(network PRIVATE THOTH_BUILD_DLL)
endif()

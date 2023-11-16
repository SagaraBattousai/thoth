
set(CRYPTO_MODULE_ROOT "${MODULE_ROOT}/thoth/crypto")

set(cpp_sources 
  "hash.cpp" 
  "keccak.cpp"
  "signing.cpp" 
  )

set(c_sources 
  "keccak.c"
  )

set(thoth_module 
  "${CRYPTO_MODULE_ROOT}/hash.h"
  "${CRYPTO_MODULE_ROOT}/keccak.h"
  "${CRYPTO_MODULE_ROOT}/signing.h"
  )

add_library(crypto SHARED ${cpp_sources} ${c_sources})

target_compile_definitions(crypto PRIVATE THOTH_BUILD_DLL)

target_sources(crypto PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${crypto_module} 
  "${MODULE_ROOT}/_thoth_config.h"
  )

#TODO: Check how private works with install
target_link_libraries(crypto PUBLIC numeric)



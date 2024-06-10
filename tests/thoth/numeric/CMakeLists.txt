
set(NUMERIC_TESTS_MODULE_ROOT "${TEST_MODULE_ROOT}/numeric")


set(cpp_sources 
  "numeric_bitstring_tests.cpp"
  "numeric_fixed_length_bitstring_tests.cpp"
  )

set(numeric_module 
  "${NUMERIC_TESTS_MODULE_ROOT}/bitstring_tests.h"
  )

add_library(numeric_tests OBJECT ${cpp_sources})

target_sources(numeric_tests PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${TEST_MODULE_BASE}
  FILES ${numeric_module}
  )

target_link_libraries(numeric_tests PUBLIC gtest numeric)

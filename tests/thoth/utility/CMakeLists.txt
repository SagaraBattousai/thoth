
set(cpp_sources 
  "utility_tests.cpp"
  )

add_library(utility_tests OBJECT ${cpp_sources})

target_link_libraries(utility_tests PUBLIC gtest utility)

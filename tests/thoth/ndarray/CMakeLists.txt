
set(cpp_sources 
  "ndarray_tests.cpp"
  )

add_library(ndarray_tests OBJECT ${cpp_sources})

target_link_libraries(ndarray_tests PUBLIC gtest ndarray)

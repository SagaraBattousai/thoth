include(TestUtils)

set(googletest_commit_hash "f8d7d77c06936315286eb55f8de22cd23c188571")

fetch_googletest(HASH "${googletest_commit_hash}" HIDDEN)

# TODO: Fix directory structure
set(testing_sources 
  "ndarray_tests.cpp" 
  "utility_tests.cpp"
  "numeric_bitstring_tests.cpp")

add_executable(thoth_tests ${testing_sources})

set_property(TARGET thoth_tests PROPERTY FOLDER Tests)
set_target_properties(gtest gtest_main gmock gmock_main
                      PROPERTIES FOLDER Tests/googleTest)

target_link_libraries(thoth_tests PRIVATE GTest::gtest_main)

# TODO: Instead of the comented out code below lets try target_link_libraries
# Find a better way to do this
# target_include_directories(
#   thoth_tests
#   PRIVATE $<TARGET_PROPERTY:concepts,INCLUDE_DIRECTORIES>
#           $<TARGET_PROPERTY:ndarray,INCLUDE_DIRECTORIES>
#           # $<TARGET_PROPERTY:network,INCLUDE_DIRECTORIES>
#           $<TARGET_PROPERTY:utility,INCLUDE_DIRECTORIES>)

target_link_libraries(thoth_tests PRIVATE numeric ndarray utility)

if(WIN32)
  copy_dlls_to_target(thoth_tests) 
endif()

include(GoogleTest)
gtest_discover_tests(thoth_tests)

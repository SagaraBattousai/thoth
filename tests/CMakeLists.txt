
include(FetchContent)

set(googletest_commit_hash "f8d7d77c06936315286eb55f8de22cd23c188571")

if (WIN32)
set(googletest_commit_hash_and_ext "${googletest_commit_hash}.zip")
else()
set(googletest_commit_hash_and_ext "${googletest_commit_hash}.tar.gz")
endif()

#VV Faster than git repo :)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/${googletest_commit_hash_and_ext}
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

if(WIN32)
  #For Windows: Prevent overriding the project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

set(testing_sources 
  "matrix.cpp"
  )

add_executable(tests ${testing_sources})

set_property(TARGET tests PROPERTY FOLDER Tests)
set_target_properties(gtest gtest_main gmock gmock_main 
  PROPERTIES FOLDER Tests/googleTest)

target_link_libraries(tests PRIVATE GTest::gtest_main)
target_include_directories(tests PRIVATE 
  $<TARGET_PROPERTY:thoth,INCLUDE_DIRECTORIES>)

if(WIN32)
  # symlink_library_to_target(tests pulse)
endif()

include(GoogleTest)
gtest_discover_tests(tests)



include(TestUtils)

set(googletest_commit_hash "f8d7d77c06936315286eb55f8de22cd23c188571")

fetch_googletest(HASH "${googletest_commit_hash}" HIDDEN)

set(ROOT_FOLDER_NAME "Tests")
set(THOTH_TESTS_FOLDER_NAME "${ROOT_FOLDER_NAME}/Thoth")
set(TEST_MODULE_BASE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(TEST_MODULE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include/thoth/tests")

add_subdirectory(thoth)

# NOTE: It tuns out we *MUST* use Object libraries as it stands.
# Below is an explanation of why we thought to switch to static libs:
#
# A lot of (smart and more knowledgeable) people recomend static libs
# over object (in the general case obviously it's case by case)
# but the arguments seem pretty solid!
#
# However, one of the benefits is exactly why we cant use static libraries
# (especially while using the default main (i.e. gtest:_main)) as unused 
# symbols are not linked with static libs. Just be aware that with 
# object library, objects are not added transitively (i.e. to consumers of 
# consumers) but in our tests this is unlikely to occur.
# 
# NOTE: Dummy (i.e. empty) source file included as some native build systems
# (such as Xcode) may not like targets that have only object files.
# Plus when we did swap to shared libs we still required it as the executable
# was empty

set(testing_root_source "testing_root.cpp")

add_executable(thoth_tests ${testing_root_source})

# NOTE: Object libs require linking (instead of generator exp) inorder to
# forward (direct) usage requirements. (however ther is a link gnerator
# expression which is the next thing to look at.
target_link_libraries(thoth_tests PRIVATE GTest::gtest_main ndarray_tests
  numeric_tests utility_tests)

set_property(TARGET thoth_tests PROPERTY FOLDER ${THOTH_TESTS_FOLDER_NAME})

set_target_properties(gtest gtest_main gmock gmock_main
                      PROPERTIES FOLDER "${ROOT_FOLDER_NAME}/googleTest")

if(WIN32)
  copy_dlls_to_target(thoth_tests) 
endif()

include(GoogleTest)
gtest_discover_tests(thoth_tests)

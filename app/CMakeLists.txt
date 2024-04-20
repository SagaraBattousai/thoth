
add_executable(app_cpp_thoth main.cpp)
add_executable(app_c_thoth main.c)

target_include_directories(app_cpp_thoth PUBLIC 
  $<TARGET_PROPERTY:ndarray,INCLUDE_DIRECTORIES>)
target_link_libraries(app_cpp_thoth numeric)
#target_link_libraries(app_cpp_thoth thoth)
#target_link_libraries(app_c_thoth thoth)

if(WIN32)
  copy_dlls_to_target(app_cpp_thoth)
  # auto_copy_dlls_for_target(app_c_thoth)
endif()

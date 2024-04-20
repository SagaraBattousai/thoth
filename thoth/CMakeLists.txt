
set(ROOT_FOLDER_NAME "Thoth")

add_subdirectory(concepts)

add_subdirectory(crypto)

add_subdirectory(ml)

add_subdirectory(ndarray)

add_subdirectory(network)

add_subdirectory(numeric)

add_subdirectory(utility)


# get_directory_property(subdirectories SUBDIRECTORIES) 

# foreach(dir ${subdirectories})
#   get_directory_property(subtargets DIRECTORY ${dir} BUILDSYSTEM_TARGETS)
#   if(subtargets)
#     set_target_properties(${subtargets} PROPERTIES FOLDER ${ROOT_FOLDER_NAME})
#   endif()
# endforeach()


# get_subtargets(subtargets DEPTH 1)
# message(STATUS "0 = ${subtargets}")
# set_target_properties(${subtargets} PROPERTIES FOLDER ${ROOT_FOLDER_NAME})
set_direct_subtargets_folder(${ROOT_FOLDER_NAME})

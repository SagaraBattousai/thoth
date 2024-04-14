set(ML_ROOT_FOLDER_NAME "${ROOT_FOLDER_NAME}/ml")


add_subdirectory(genetic)


get_directory_property(subdirectories SUBDIRECTORIES) 

foreach(dir ${subdirectories})
  get_directory_property(subtargets DIRECTORY ${dir} BUILDSYSTEM_TARGETS)
  if(subtargets)
    set_target_properties(${subtargets} PROPERTIES FOLDER ${ML_ROOT_FOLDER_NAME})
  endif()
endforeach()



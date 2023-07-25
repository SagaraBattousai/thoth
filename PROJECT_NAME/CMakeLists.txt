
#set(<Project_Name>_MODULE_ROOT "${MODULE_ROOT}/pulse")
set(<Project_Name>_INCLUDE_ROOT "${INCLUDE_ROOT}/<Project_Name>")

add_subdirectory(<Sub_Project>)

add_library(<Project_Name> SHARED #STATIC  
  ${includes}
  ${sources}
  $<TARGET_OBJECTS:>
  )

target_link_libraries(<Project_Name> PUBLIC )

set_target_properties(<Targets> PROPERTIES FOLDER <Folder_Name>)

target_sources(<Project_Name> PUBLIC
  FILE_SET headers 
  TYPE HEADERS
  BASE_DIRS ${INCLUDE_ROOT}
  FILES ${<Project_Name>_INCLUDE_ROOT}
  )




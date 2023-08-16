
# Set: DOXYGEN_INPUT_FILES based on passed in targets' sources.
function(set_doxygen_input_files)
  if(ARGC LESS 1)
    message(WARNING "Needs additional arguments; namely targets \
    whos source files require/want documentation.")
    return()
  endif()

  foreach(target ${ARGN})
    #get_target_property(target_sources ${target} SOURCES)
    #Switching to header set as we document in the header
    get_target_property(target_sources ${target} HEADER_SET)

    foreach(source ${target_sources})    
    # BASE_DIRECTORY unneeded as this file is in the same directory as
    # Doxygen.in 
      cmake_path(
        RELATIVE_PATH source
        OUTPUT_VARIABLE source_relative_to_doxygen)

      list(APPEND DOCUMENTED_HEADERS ${source_relative_to_doxygen})
    endforeach()
  endforeach()

  set(DOXYGEN_INPUT_FILES ${DOCUMENTED_HEADERS} PARENT_SCOPE)
  list(JOIN DOCUMENTED_HEADERS " " INPUT_FILES)
  set(DOXYGEN_INPUT_FILES ${INPUT_FILES} PARENT_SCOPE)

endfunction()




# The following Variables must be set: 
# { DOXYGEN_INPUT_FILES, DOXYGEN_OUTPUT_DIRECTORY, DOXYGEN_XML_INDEX_FILE,
#   DOXYFILE_IN, DOXYFILE_OUT }

macro(configure_doxygen_and_add_command)
  set(DOXYGEN_GENERATE_XML YES)
  set(DOXYGEN_GENERATE_HTML NO)
  set(DOXYGEN_GENERATE_MAN YES)
  set(DOXYGEN_GENERATE_LATEX NO)
  set(DOXYGEN_JAVADOC_BANNER YES)

  configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

  #Can't use doxygen_add_docs as we need doxyfile to be usable for read-the-docs.
  add_custom_command(OUTPUT ${DOXYGEN_XML_INDEX_FILE}
    DEPENDS ${DOXYFILE_IN}
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
    MAIN_DEPENDENCY ${DOXYFILE_OUT}
    #^^ I don't really get what its for in vs, what does hang mean?
    #VV As this is a macro, this will be the directory of the caller! :)
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating Doxygen Documentation ...")
endmacro()

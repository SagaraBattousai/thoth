
#Keeping others just for now, will be removed in the future. Will use copy as 
#copy if different was causing an issue ( I think/remember)
function(auto_copy_dlls_for_target target)
  add_custom_command(TARGET ${target} 
    POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_RUNTIME_DLLS:${target}>
    $<TARGET_FILE_DIR:${target}>
  COMMAND_EXPAND_LISTS
)
endfunction()

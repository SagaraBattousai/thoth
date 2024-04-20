# Keeping others just for now, will be removed in the future. Will use copy as
# copy if different was causing an issue ( I think/remember)
#
# Unfortunatly this must be called in the directory where the target is defined
# so we can't get them all dynamically
function(copy_dlls_to_target target)
  add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${target}>
            $<TARGET_RUNTIME_DLLS:${target}>
    COMMAND_EXPAND_LISTS)
endfunction()




set(ROOT_FOLDER_NAME "Thoth")

add_subdirectory(concepts)

add_subdirectory(crypto)

add_subdirectory(ml)

add_subdirectory(ndarray)

add_subdirectory(network)

add_subdirectory(numeric)

add_subdirectory(random)

add_subdirectory(utility)


set_direct_subtargets_folder(${ROOT_FOLDER_NAME})

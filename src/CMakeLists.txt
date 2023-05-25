
add_library(utils utils.h utils.c)
add_library(constants constants.h constants.c)
add_library(client_funcs client_funcs.h client_funcs.c)

add_executable(server server.c)

add_executable(client client.c)
target_link_libraries(client client_funcs)

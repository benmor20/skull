
add_library(utils utils.h utils.c)
add_library(constants constants.h constants.c)

add_library(client_funcs client_funcs.h client_funcs.c)
link_libraries(client_funcs utils)

add_library(server_funcs server_funcs.h server_funcs.c)
link_libraries(server_funcs utils)

add_executable(server server.c)
target_link_libraries(server server_funcs)

add_executable(client client.c)
target_link_libraries(client client_funcs)

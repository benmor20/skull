
add_library(utils utils.h utils.c)
add_library(constants constants.h constants.c)

add_executable(server server.c)

add_executable(client client.c)

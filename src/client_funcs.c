#include "client_funcs.h"

#include "utils.h"

void try_connect(int client_socket, struct sockaddr_in server_addr) {
    if (connect(client_socket, (const struct sockaddr *) &server_addr,
            sizeof(server_addr)) == -1) {
        error_and_exit("Unable to connect to server.");
    }
}

FILE* get_socket_file(int client_socket) {
    FILE* socket_file = fdopen(client_socket, "w+");
    if (socket_file == NULL) {
        error_and_exit("Unable to open socket descriptor as a file.");
    }
    return socket_file;
}

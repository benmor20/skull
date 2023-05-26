#include "client_funcs.h"

#include "utils.h"

void try_connect(int client_socket, struct sockaddr_in server_addr) {
    if (connect(client_socket, (const struct sockaddr *) &server_addr,
            sizeof(server_addr)) == -1) {
        error_and_exit("Unable to connect to server.");
    }
}

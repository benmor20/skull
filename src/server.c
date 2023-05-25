

#include "server_funcs.h"
#include "constants.h"
#include "utils.h"

void hello_world_server(int client_socket) {
}

// Code modified from olincollege/softsys A8
int main(void) {
    // Create server
    struct sockaddr_in server_addr = socket_address(INADDR_LOOPBACK,
                                                    LISTEN_PORT);
    Server* server = make_server(server_addr, hello_world_server);

    // Setup listener and accept clients
    listen_for_connections(server);
    while (accept_client(server) != -1) {
        accept_client(server);
    }

    // Clean up and return
    free_server(server);
    return 0;
}

#include <arpa/inet.h>

#include "utils.h"
#include "client_funcs.h"
#include "constants.h"

// Code modified from olincollege/softsys A8
int main(void) {
    // Connect to server
    int socket = open_tcp_socket();
    struct sockaddr_in server_addr = socket_address(INADDR_LOOPBACK,
            LISTEN_PORT);
    try_connect(socket, server_addr);

    // Run client
    FILE* socket_file = get_socket_file(socket);
    int socket_file_status = 0;
    while (socket_file_status != -1) {
        socket_file_status = -1; // TODO replace with actual client function
    }

    // If we didn't hit the end of the file, something went wrong
    if (!feof(stdin) && !feof(socket_file)) {
        error_and_exit("Error reading or writing line.");
    }

    // Clean up and exit
    close_tcp_socket(socket);
    return 0;
}

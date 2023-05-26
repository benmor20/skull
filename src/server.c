
#include <stdio.h>
#include <string.h>
#include "server_funcs.h"
#include "constants.h"
#include "utils.h"

void hello_world_server(int client_socket) {
    FILE* client_file = fdopen(client_socket, "r+");
    if (client_file == NULL) {
        error_and_exit("Error opening client_file file");
    }
    char* line = NULL;
    size_t len = 0;
    while (1) {
        if (fprintf(client_file, "Hello, ") <= 0) {
            error_and_exit("Error writing to client_file");
        }
        puts("Sent text");
        if (getline(&line, &len, client_file) == -1) {
            error_and_exit("Error reading line");
        }
        printf("Received %s\n", line);
        if (strcmp(line, "World!") == 0) {
            return;
        }
        puts("Line unaccepted, continuing");
    }
}

// Code modified from olincollege/softsys A8
int main(void) {
    // Create server
    struct sockaddr_in server_addr = socket_address(INADDR_LOOPBACK,
                                                    LISTEN_PORT);
    Server* server = make_server(server_addr, hello_world_server);

    // Setup listener and accept clients
    listen_for_connections(server);
    int accept_status = 0;
    while (accept_status != -1) {
        accept_status = accept_client(server);
        puts("Accepted client");
    }

    // Clean up and return
    free_server(server);
    return 0;
}

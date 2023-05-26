
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server_funcs.h"
#include "communication.h"
#include "constants.h"
#include "utils.h"

void hello_world_server(int client_socket) {
    FILE* client_file = get_socket_file(client_socket);
    char* line = NULL;
    while (1) {
        send_message(client_file, "Hello,\n");
        puts("Sent text");
        line = read_message(client_file, NULL);
        printf("Received %s", line);
        if (strcmp(line, "World!\n") == 0) {
            puts("Accepted!");
            free(line);
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

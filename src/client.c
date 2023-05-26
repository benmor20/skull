#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "client_funcs.h"
#include "constants.h"

int hello_world_client(FILE* socket_file) {
    char* recv_line = NULL;
    size_t recv_line_size = 0;
    puts("Waiting for server...");
    if (getline(&recv_line, &recv_line_size, socket_file) == -1) {
        return -1;
    }
    puts("Received line");
    printf("%s", recv_line);
    free(recv_line);

    char* send_line = NULL;
    size_t send_line_size = 0;
    if (getline(&send_line, &send_line_size, stdin) == -1) {
        return -1;
    }
    puts("Got input");
    // If we can't send the line on the socket, the connection is broken and we
    // have to exit.
    if (fputs(send_line, socket_file) == EOF) {
        free(send_line);
        error_and_exit("Couldn't send line");
    }
    puts("Sent input");
    free(send_line);
    return 0;
}

// Code modified from olincollege/softsys A8
int main(void) {
    // Connect to server
    int socket = open_tcp_socket();
    struct sockaddr_in server_addr = socket_address(INADDR_LOOPBACK,
            LISTEN_PORT);
    try_connect(socket, server_addr);
    puts("Connected");

    // Run client
    FILE* socket_file = get_socket_file(socket);
    int socket_file_status = 0;
    while (socket_file_status != -1) {
        socket_file_status = hello_world_client(socket_file);
    }

    // If we didn't hit the end of the file, something went wrong
    if (!feof(stdin) && !feof(socket_file)) {
        error_and_exit("Error reading or writing line.");
    }

    // Clean up and exit
    close_tcp_socket(socket);
    return 0;
}

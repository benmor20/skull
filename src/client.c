#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "client_funcs.h"
#include "communication.h"
#include "constants.h"

int hello_world_client(FILE* socket_file) {
    char* recv_line = read_message(socket_file, NULL);
    printf("%s", recv_line);
    free(recv_line);

    char* send_line = read_message(stdin, NULL);
    puts("Got input");
    send_message(socket_file, send_line);
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

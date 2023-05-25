#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // close

noreturn void error_and_exit(const char* msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int open_tcp_socket(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_and_exit("Could not create socket");
    }
    return sock;
}

void close_tcp_socket(int socket_descriptor) {
    if (close(socket_descriptor) == -1) {
        error_and_exit("Unable to close socket");
    }
}

struct sockaddr_in socket_address(in_addr_t addr, in_port_t port) {
    struct sockaddr_in res;
    res.sin_addr.s_addr = htonl(addr);
    res.sin_port = htons(port);
    res.sin_family = AF_INET;
    return res;
}

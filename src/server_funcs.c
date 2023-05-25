#include "server_funcs.h"
#include "constants.h"
#include "utils.h"

#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

Server* make_server(struct sockaddr_in listener_addr, ServerProcess process) {
    Server* server = malloc(sizeof(Server));
    server->addr = listener_addr;
    server->max_backlog = MAX_BACKLOG;
    server->listener = open_tcp_socket();
    server->process = process;
    return server;
}

void free_server(Server* server) {
    close_tcp_socket(server->listener);
    free(server);
}

void listen_for_connections(Server* server) {
    if (bind(server->listener, (const struct sockaddr *) &server->addr,
            sizeof(struct sockaddr_in)) == -1) {
        error_and_exit("Unable to bind listener");
    }
    if (listen(server->listener, server->max_backlog) == -1) {
        error_and_exit("Unable to listen on listener socket");
    }
}

int accept_client(Server* server) {
    // Accept the client
    socklen_t client_addr_len = sizeof(struct sockaddr_storage);
    struct sockaddr_storage* client_addr = malloc(client_addr_len);
    int clientfd = accept(server->listener, (struct sockaddr*)client_addr,
                           &client_addr_len);
    free(client_addr);
    if (clientfd == -1) {
        error_and_exit("Unable to accept client");
    }

    // Fork
    pid_t pid = fork();
    switch (pid) {
        case -1:
            error_and_exit("Error while forking");
        case 0:
            // Child; run the process
            server->process(clientfd);
            return -1;
        default:
            // Parent; return to accept the next client
            return 0;
    }
}

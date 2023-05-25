#pragma once

#include <netinet/in.h>

/**
 * A pointer to the function a server runs.
 *
 * Takes as input an int, the client socket descriptor, and returns nothing.
 */
typedef void (*ServerProcess)(int);

typedef struct {
    // The socket descriptor to listen for connections
    int listener;

    // The address for the listener
    struct sockaddr_in addr;

    // The maximum number of clients that can be waiting to be let in
    int max_backlog;

    // The function to run when a client is accepted
    ServerProcess process;
} Server;

/**
 * Create a new server with the given listener address and process
 *
 * Define and return a Server struct with the given listener address and
 * default max backlog and port. When a new client is accepted, the server
 * will run the given ServerProcess function. This server's data is created in
 * dynamic memory, so the caller is responsible for freeing the returned
 * value using free_server.
 *
 * Code modified from olincollege/softsys A8
 *
 * @param listener_addr the IPv4 address and port to listen on
 * @param process a pointer to the server's process
 * @return a pointer to the created Server struct
 */
Server* make_server(struct sockaddr_in listener_addr, ServerProcess process);

/**
 * Free a Server struct
 *
 * Attempting to free an uninitialized server, server dynamic memory that has
 * already been freed, or a pointer to memory representing anything other
 * than an echo_server instance will result in undefined behavior.
 *
 * Code modified from olincollege/softsys A8
 *
 * @param server the Server to free
 */
void free_server(Server* server);

/**
 * Start listening on a server for potential client connections.
 *
 * Bind the listener socket and set it to listen for client connection requests.
 * The listener socket is part of the server's internal data and does not need
 * to be opened separately. In the event that binding or listening on the socket
 * fails, print an error message and exit the program without returning.
 *
 * Code taken from olincollege/softsys A8
 *
 * @param server The server to start listening on.
 */
void listen_for_connections(Server* server);

/**
 * Accept a new client connection and start the echo process.
 *
 * Wait until a client connection request comes in, accepting it. Once accepted,
 * fork a new process. In the child process, run the server's process, and in
 * the parent, end the function. The server program should run the function in a
 * loop, whereas the child can exit the function after the process is run. In
 * the event of an error in accepting a connection or forking a new process,
 * print an appropriate error message and exit the program.
 *
 * Code modified from olincollege/softsys A8
 *
 * @param server The server to accept the connection on.
 * @return 0 for the parent process and -1 for the child (server's) process.
 */
int accept_client(Server* server);

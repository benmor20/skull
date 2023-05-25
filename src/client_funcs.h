#pragma once

#include <netinet/in.h>  // sockaddr_in
#include <stdio.h>       // FILE

/**
 * Attempt to connect the client to the server, or exit on failure.
 *
 * Code taken from olincollege/softsys A8
 *
 * @param client_socket the socket descriptor for the client
 * @param server_addr the server address to connect to.
 */
void try_connect(int client_socket, struct sockaddr_in server_addr);


/**
 * Get a write-only file pointer for the given client socket descriptor.
 *
 * Given a socket descriptor that is connected to a server, create and return
 * a file pointer for that socket for use with high-level functions. If
 * unsuccessful, this function will error and exit, not returning.
 *
 * Code taken from olincollege/softsys A8
 *
 * @param client_socket a socket descriptor to create a file for
 * @return a file pointer for the given socket descriptor
 */
FILE* get_socket_file(int client_socket);

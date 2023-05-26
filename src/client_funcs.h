#pragma once

#include <netinet/in.h>

/**
 * Attempt to connect the client to the server, or exit on failure.
 *
 * Code taken from olincollege/softsys A8
 *
 * @param client_socket the socket descriptor for the client
 * @param server_addr the server address to connect to.
 */
void try_connect(int client_socket, struct sockaddr_in server_addr);

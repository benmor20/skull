#pragma once

#include <netinet/in.h>
#include <stdnoreturn.h>

/**
 * Display an error and then exit the program.
 *
 * Prints the message to the standard output, along with a more specific message
 * given by errno, which should be set by the previous function to run. This
 * function then exits the program and so does not return.
 *
 * Function taken from olincollege/softsys A8
 *
 * @param msg the message to display, describing the context of the error
 */
noreturn void error_and_exit(const char* msg);

/**
 * Attempt to open an IPv4 TCP socket.
 *
 * Try to create a TCP socket on IPv4, and return the socket descriptor if
 * successful. If creating the socket is not successful, print an error message
 * and exit the program without returning from the function.
 *
 * Function taken from olincollege/softsys A8
 *
 * @return A socket descriptor corresponding to the new socket.
 */
int open_tcp_socket(void);

/**
 * Attempt to close an open socket.
 *
 * Try to close an existing socket given its descriptor. If closing the socket
 * is not successful, print an error message and exit the program. In the case
 * of an error, this function does not return.
 *
 * Function taken from olincollege/softsys A8
 *
 * @param socket_descriptor The descriptor for the socket to close.
 */
void close_tcp_socket(int socket_descriptor);

/**
 * Return the sockaddr_in corresponding to an address and port.
 *
 * Given an address and port number, convert their representations to network
 * byte order and assemble them into an approopriate sockaddr_in. The returned
 * value can then be used to bind to or connect to a socket.
 *
 * Function taken from olincollege/softsys A8
 *
 * @param addr The address to bind or connect the socket to, in host order.
 * @param port The port number to bind or connect the socket to, in host order.
 * @return A sockaddr_in structure to use with bind/connect, in network order.
 */
struct sockaddr_in socket_address(in_addr_t addr, in_port_t port);

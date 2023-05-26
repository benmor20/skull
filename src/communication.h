#pragma once

#include <stdio.h>

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

/**
 * Communicates a message across the server/client bridge.
 *
 * If an error occurs while writing to the file, this function will error and
 * exit, not returning.
 *
 * @param socket_file the communication bridge between the server and client
 * @param msg the message to send
 */
void send_message(FILE* socket_file, const char* msg);

/**
 * Waits until a line has been sent over the server/client bridge, then reads
 * and returns it, optionally storing its length.
 *
 * The resulting string is allocated dynamically by virtue of get_line, so
 * the user is responsible for freeing it. If an error occurs while trying to
 * read the line, this function will error and exit, not returning.
 *
 * @param socket_file the communication bridge between the server and client
 * @param len the location to store the length of the returned string, or
 *      NULL to ignore its value
 * @return one line sent over the communication bridge
 */
char* read_message(FILE* socket_file, size_t* len);

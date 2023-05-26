#include "communication.h"
#include "utils.h"

FILE* get_socket_file(int client_socket) {
    FILE* socket_file = fdopen(client_socket, "r+");
    if (socket_file == NULL) {
        error_and_exit("Unable to open socket descriptor as a file.");
    }
    return socket_file;
}

void send_message(FILE* socket_file, const char* msg) {
    if (fputs(msg, socket_file) <= 0) {
        error_and_exit("Error while sending message");
    }
}

char* read_message(FILE* socket_file, size_t* len) {
    char* line = NULL;
    size_t temp_len = -1;
    if (getline(&line, &temp_len, socket_file) == -1) {
        error_and_exit("Error reading line");
    }
    if (len != NULL) {
        *len = temp_len;
    }
    return line;
}

/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Server include, contain struct and function
*/

#if !defined(_SERVER_H)
#define _SERVER_H

#include <netinet/in.h>
#include <sys/select.h>
#include <stdbool.h>
#include "argument.h"
#include "client.h"

// the maximum of pending connection used by listen()
#define MAXIMUM_PENDING_CONNECTION 5

// server's fd_set
#define NUMBER_OF_SET 3
#define READING_SET 0
#define WRITING_SET 1
#define WORKING_SET 2

enum server_error_type_s {
    OTHER,
    FATAL,
    CONTINUE
};

typedef enum server_error_type_s server_error_type_t;


struct server_error_s {
    char *msg;
    server_error_type_t err_type;
};

typedef struct server_error_s server_error_t;


struct server_s {
    int port;
    char *d_path;
    int socket;
    struct sockaddr_in info;
    int nb_client;
    client_t *clients;
    server_error_t err;
    fd_set sets[NUMBER_OF_SET];
};

typedef struct server_s server_t;

server_t init_server(const argument_t args);
void init_server_connection(server_t *server);
server_error_t new_server_error(server_error_type_t type, char *message);

#endif // _SERVER_H

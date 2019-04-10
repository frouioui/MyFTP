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
#define NUMBER_OF_SET 4
#define READING_SET 0
#define WRITING_SET 1
#define READWORK_SET 2
#define WRITEWORK_SET 3

// server reponses
#define RESP_200 "200 OK.\r\n"
#define RESP_214 "214 Help message\nUSER PASS HELP PWD CWD NOOP QUIT\n"\
                "214 OK\r\n"
#define RESP_220 "220 Connected.\r\n"
#define RESP_221 "221 Goodbye.\r\n"
#define RESP_230 "230 User logged in, proceed. Logged out if appropriate.\r\n"
#define RESP_250 "250 Directory successfully changed.\r\n"
#define RESP_331 "331 User name okay, need password.\r\n"
#define RESP_332 "332 Need account for login.\r\n"
#define RESP_430 "430 Invalid username or password.\r\n"
#define RESP_503 "503 Invalid sequence of command.\r\n"
#define RESP_530 "530 This FTP server is anonymous only.\r\n"
#define RESP_530_NEED_CONNECT "530 Please login first.\r\n"
#define RESP_550 "550 Failed to change directory.\r\n"

enum server_error_type_s {
    NONE,
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
void server_start(server_t *server);
void add_client_to_server(server_t *server, const client_t client);
void server_remove_client(server_t *server, const int socket);

#endif // _SERVER_H

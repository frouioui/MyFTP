/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Client function and struct
*/

#if !defined(_CLIENT_H)
#define _CLIENT_H

#include "user.h"
#include "msg_queue.h"

enum data_transfert_mode_s {
    NOT_SET,
    PASSIVE,
    ACTIVE
};

typedef enum data_transfert_mode_s data_transfert_mode_t;


struct client_s {
    user_t user;
    message_queue_t write_queue;
    message_queue_t read_queue;
    data_transfert_mode_t dt_mode;
    int dt_socket;
    int socket;
    char *path;
    char *parent_path;
};

typedef struct client_s client_t;

void handle_io(void *server);
void handle_read_client(void *server);
void handle_write_client(void *server);
client_t connect_new_client(void *server);
void init_client_queues(client_t *client);
void handle_old_client(void *server, const int client_fd, bool r, bool w);
char *get_current_path(const client_t *client);

#endif // _CLIENT_H

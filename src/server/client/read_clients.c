/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Read from client
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "server.h"
#include "client.h"
#include "msg_queue.h"

static void handle_new_connection(server_t *server)
{
    client_t client = {0};

    client = connect_new_client(server);
    init_client_queues(&client);
    if (server->err.err_type != NONE) {
        return;
    }
    append_new_message(&client.write_queue, "202\r\n");
    add_client_to_server(server, client);
    // TODO: log new connection
    printf("new connection\n");
}

static void handle_single_client(server_t *server, const int cur_fd)
{
    if (cur_fd == server->socket) {
        handle_new_connection(server);
    } else {
        handle_old_client(server, cur_fd);
    }
}

void handle_read_client(void *server)
{
    server_t *srv = server;

    for (unsigned int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &srv->sets[READWORK_SET]) == true) {
            handle_single_client(server, i);
        }
    }
}
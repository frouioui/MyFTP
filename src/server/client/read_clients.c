/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Read from client
*/

#include <stdlib.h>
#include "server.h"

static void handle_client(server_t *server, const int cur_fd)
{
    if (cur_fd == server->socket) {
        // accept client
        // connect to it
    } else {
        // run single client
    }
}

void handle_read_client(void *server)
{
    server_t *srv = server;

    for (unsigned int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &srv->sets[READWORK_SET]) == true) {
            handle_client(server, i);
        }
    }
}
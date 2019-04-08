/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Main file of the write functions for client
*/

#include "server.h"
#include "client.h"

static void handle_single_client(server_t *server, const int cur_fd)
{
    if (cur_fd == server->socket) {
    } else {
        handle_old_client(server, cur_fd, false, true);
    }
}

void handle_write_client(void *server)
{
    server_t *srv = server;

    for (unsigned int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &srv->sets[WRITEWORK_SET]) == true) {
            handle_single_client(server, i);
        }
    }
}
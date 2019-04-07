/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Handle an old client connection
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "msg_queue.h"
#include "server.h"
#include "client.h"
#include "command.h"

static client_t find_request_client(server_t *server, const int client_fd)
{
    client_t empty = {0};

    for (int i = 0; i < server->nb_client; i++) {
        if (server->clients[i].socket == client_fd) {
            return (server->clients[i]);
        }
    }
    return (empty);
}

static void read_client(client_t *client)
{
    char buf1[2] = {0};
    char *buf = NULL;
    char c = 0;

    for (int ret = 1; ret > 0 && !is_last_message_done(&client->read_queue);) {
        ret = read(client->socket, &c, 1);
        buf1[0] = c;
        buf = strdup(buf1);
        append_new_message(&client->read_queue, buf);
        free(buf);
    }
}

void handle_old_client(void *server, const int client_fd)
{
    server_t *srv = server;
    client_t client = find_request_client(srv, client_fd);

    if (client.socket != client_fd)
        return;
    read_client(&client);
    execute_last_command(server, &client);
}
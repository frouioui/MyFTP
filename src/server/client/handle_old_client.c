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
#include <sys/types.h>
#include <sys/stat.h>
#include "msg_queue.h"
#include "server.h"
#include "client.h"
#include "command.h"

static client_t *find_request_client(server_t *server, const int client_fd)
{
    for (int i = 0; i < server->nb_client; i++) {
        if (server->clients[i].socket == client_fd) {
            return (&server->clients[i]);
        }
    }
    return (NULL);
}

static bool read_client(server_t *server, client_t *client)
{
    char buf1[2] = {0};
    char *buf = NULL;
    char c = 0;

    for (int ret = 1; ret > 0 && !is_last_message_done(&client->read_queue);) {
        ret = read(client->socket, &c, 1);
        if (ret == 0 && c == 0) {
            FD_CLR(client->socket, &server->sets[WRITING_SET]);
            FD_CLR(client->socket, &server->sets[READING_SET]);
            user_quit(server, client, "");
            return (false);
        }
        buf1[0] = c;
        buf = strdup(buf1);
        append_new_message(&client->read_queue, buf);
        free(buf);
    }
    return (true);
}

static void write_client(server_t *server, client_t *client)
{
    int ret = 1;
    char *c = 0;

    while (ret > 0) {
        c = read_and_trim_last_message(&client->write_queue, 1);
        if (c == NULL)
            break;
        ret = write(client->socket, c, 1);
        free(c);
    }
    if (client->write_queue.nb_msg == 0) {
        FD_CLR(client->socket, &server->sets[WRITING_SET]);
    }
}

void handle_old_client(void *server, const int client_fd, bool r, bool w)
{
    server_t *srv = server;
    client_t *client = find_request_client(srv, client_fd);

    if (client == NULL) {
        printf("New [unknown] client tried to connect.\n");
        return;
    }
    if (client->socket != client_fd)
        return;
    if (r) {
        if (read_client(server, client) == false)
            return;
        execute_last_command(server, client);
    } else if (w) {
        write_client(server, client);
    }
}
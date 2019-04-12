/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** CDUP command, change to parent directory
*/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "server.h"
#include "client.h"
#include "msg_queue.h"
#include "command.h"
#include "string_parser.h"

static char *correct_path(char *path, char *r_path, char *a_path)
{
    if (path == NULL) {
        return (strdup(a_path));
    } else if (strncmp(path, a_path, strlen(r_path))) {
        return (strdup(r_path));
    }
    return (path);
}

void cdup_user(server_t *server, client_t *client, char *cmd)
{
    char *path = NULL;
    char *buf = NULL;

    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else {
        path = calloc(1, sizeof(char) * (strlen(client->path) + 4));
        path = strcat(path, client->path);
        path = strcat(path, "/..");
        buf = realpath(path, NULL);
        free(path);
        buf = correct_path(buf, client->parent_path, client->path);
        free(client->path);
        client->path = buf;
        append_new_message(&client->write_queue, RESP_250);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
    (void)cmd;
}
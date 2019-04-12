/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Delete a file
*/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "server.h"
#include "client.h"
#include "msg_queue.h"
#include "command.h"
#include "string_parser.h"

void delete_file_user(server_t *server, client_t *client, char *cmd)
{
    char *cmd_path = NULL;

    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else {
        cmd_path = calloc(1, sizeof(char) *
            (strlen(client->path) + strlen(cmd) + 4));
        cmd_path = strcat(cmd_path, client->path);
        cmd_path = strcat(cmd_path, "/");
        cmd_path = strcat(cmd_path, cmd);
        cmd_path = realpath(cmd_path, NULL);
        if (cmd_path == NULL ||
        strncmp(cmd_path, client->path, strlen(client->parent_path)) != 0
            || unlink(cmd_path) < 0) {
            append_new_message(&client->write_queue, RESP_550);
            return;
        }
        append_new_message(&client->write_queue, RESP_250);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}

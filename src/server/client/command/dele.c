/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Delete a file
*/

/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Source file of the CDW command
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
    char *root = NULL;
    char *root_2 = NULL;

    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else {
        cmd_path = realpath(cmd, NULL);
        root = realpath(client->parent_path, NULL);
        root_2 = realpath(client->path, NULL);
        if (cmd_path == NULL ||
        strncmp(cmd_path, root_2, strlen(root)) != 0 || unlink(cmd) < 0) {
            append_new_message(&client->write_queue, RESP_550);
            return;
        }
        append_new_message(&client->write_queue, RESP_250);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}

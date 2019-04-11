/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** PWD command functions
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

void pwd_user(server_t *server, client_t *client, char *cmd)
{
    char *path = NULL;
    char *msg = NULL;

    (void)cmd;
    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else {
        path = get_current_path(client);
        msg = calloc(1, sizeof(char) * (strlen(RESP_257) + strlen(path) +
            strlen("\r\n") + 6));
        strcat(msg, RESP_257);
        strcat(msg, "\"");
        strcat(msg, path);
        strcat(msg, "\"\r\n");
        append_new_message(&client->write_queue, msg);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}
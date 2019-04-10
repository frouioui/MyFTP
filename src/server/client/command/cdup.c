/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** CDUP command, change to parent directory
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "client.h"
#include "msg_queue.h"
#include "command.h"
#include "string_parser.h"

void cdup_user(server_t *server, client_t *client, char *cmd)
{
    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else {
        append_new_message(&client->write_queue, RESP_250);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
    (void)cmd;
}
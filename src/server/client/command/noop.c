/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Handle the login of the user
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include "client.h"
#include "command.h"
#include "string_parser.h"
#include "user.h"
#include "msg_queue.h"

void noop_user(server_t *server, client_t *client, char *cmd)
{
    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else {
        append_new_message(&client->write_queue, RESP_200);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
    (void)cmd;
}


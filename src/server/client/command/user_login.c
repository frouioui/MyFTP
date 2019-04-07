/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Handle the login of the user
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "client.h"
#include "command.h"
#include "string_parser.h"

void user_login(server_t *server, client_t *client, char *cmd)
{
    client->user.name = strdup(cmd);
    str_to_lower_case(client->user.name);
    if (is_username_correct(client->user.name) == false) {
        append_new_message(&client->write_queue, RESP_530);
        free(client->user.name);
        client->user.name = NULL;
    } else {
        append_new_message(&client->write_queue, RESP_331);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
    (void)server;
}

void user_password(server_t *server, client_t *client, char *cmd)
{
    (void)cmd;
    (void)server;
    (void)client;
}
/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Handle the login of the user
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "client.h"
#include "command.h"
#include "string_parser.h"
#include "user.h"

void user_login(server_t *server, client_t *client, char *cmd)
{
    if (client->user.name != NULL) {
        free(client->user.name);
        client->user.name = NULL;
    }
    client->user.name = strdup(cmd);
    str_to_lower_case(client->user.name);
    trim_str(client->user.name, "\r\n");
    if (is_username_correct(client->user.name) == false) {
        append_new_message(&client->write_queue, RESP_530);
        free(client->user.name);
    } else if (client->user.pass != NULL && client->user.name != NULL) {
        if (pass_and_user_valid(client->user) == true) {
            append_new_message(&client->write_queue, RESP_230);
        } else {
            append_new_message(&client->write_queue, RESP_430);
        }
    } else {
        append_new_message(&client->write_queue, RESP_331);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}

void user_password(server_t *server, client_t *client, char *cmd)
{
    if (client->user.pass != NULL) {
        free(client->user.pass);
        client->user.pass = NULL;
    }
    client->user.pass = strdup(cmd);
    str_to_lower_case(client->user.pass);
    trim_str(client->user.pass, "\r\n");
    if (client->user.pass != NULL && client->user.name != NULL) {
        if (pass_and_user_valid(client->user) == true) {
            append_new_message(&client->write_queue, RESP_230);
        } else {
            append_new_message(&client->write_queue, RESP_430);
        }
    } else {
        append_new_message(&client->write_queue, RESP_332);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}
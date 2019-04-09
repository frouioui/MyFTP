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

void user_login(server_t *server, client_t *client, char *cmd)
{
    if (client->user.name != NULL) {
        free(client->user.name);
        client->user.name = NULL;
    }
    client->user.name = strdup(cmd);
    if (is_username_correct(client->user.name) == false) {
        append_new_message(&client->write_queue, RESP_530);
        free(client->user.name);
        client->user.name = NULL;
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

void user_quit(server_t *server, client_t *client, char *cmd)
{
    if (client->user.name != NULL)
        free(client->user.name);
    if (client->user.pass != NULL)
        free(client->user.pass);
    free(client->path);
    destroy_message_queue(&client->read_queue);
    destroy_message_queue(&client->write_queue);
    write(client->socket, RESP_221, strlen(RESP_221));
    server_remove_client(server, client->socket);
    FD_CLR(client->socket, &server->sets[WRITING_SET]);
    FD_CLR(client->socket, &server->sets[READING_SET]);
    close(client->socket);
    (void)cmd;
}

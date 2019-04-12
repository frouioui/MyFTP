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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/ftp.h>
#include <unistd.h>
#include "server.h"
#include "client.h"
#include "msg_queue.h"
#include "command.h"
#include "string_parser.h"
#include "socket.h"

static int accept_data(client_t *client)
{
    int addrlen = sizeof(client->dt_info);
    int dsock = accept(client->dt_socket, (struct sockaddr *)&client->dt_info,
            (socklen_t *)&addrlen);

    return (dsock);
}

void retr(server_t *server, client_t *client, char *cmd)
{
    (void)cmd;
    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else if (client->dt_mode != PASSIVE) {
        append_new_message(&client->write_queue, RESP_425);
    } else {
        accept_data(client);
        append_new_message(&client->write_queue, RESP_150);
        close(client->dt_socket);
        client->dt_mode = NOT_SET;
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}
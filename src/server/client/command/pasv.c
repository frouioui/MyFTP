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
#include "server.h"
#include "client.h"
#include "msg_queue.h"
#include "command.h"
#include "string_parser.h"
#include "socket.h"

static char *get_ip_string(char *ip, char *msg)
{
    char *tok = NULL;
    int i = 0;

    while ((tok = strsep(&ip, ".")) != NULL && i < 4) {
        if (i < 3) {
            msg = strcat(strcat(msg, tok), ",");
        } else {
            msg = strcat(msg, tok);
        }
        i++;
    }
    return (msg);
}

static char *create_new_client_information(server_t *server, client_t *client)
{
    char *msg = calloc(1, sizeof(char) * 255);
    char *port = calloc(1, sizeof(char) * 255);
    struct sockaddr_in new_in = create_socket_internet_address(0);
    char *tmp_ip = NULL;
    socklen_t size = 0;

    client->dt_socket = create_socket();
    client->dt_mode = PASSIVE;
    bind_socket(client->dt_socket, &new_in, true);
    size = sizeof(new_in);
    getsockname(client->dt_socket, (struct sockaddr *)&new_in, &size);
    tmp_ip = strdup(inet_ntoa(server->info.sin_addr));
    listen_socket(client->dt_socket, MAXIMUM_PENDING_CONNECTION);
    msg = get_ip_string(tmp_ip, msg);
    sprintf(port, ",%d,%d).\r\n", ntohs(new_in.sin_port) / 256,
        ntohs(new_in.sin_port) % 256);
    msg = strcat(msg, port);
    client->dt_info = new_in;
    return (msg);
}

void pasv(server_t *server, client_t *client, char *cmd)
{
    char *final_msg = NULL;
    char *msg = NULL;

    (void)cmd;
    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else {
        msg = create_new_client_information(server, client);
        final_msg = calloc(1, sizeof(char) * (strlen(msg) + strlen(RESP_227) +
            1));
        final_msg = strcat(final_msg, RESP_227);
        final_msg = strcat(final_msg, msg);
        append_new_message(&client->write_queue, final_msg);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}
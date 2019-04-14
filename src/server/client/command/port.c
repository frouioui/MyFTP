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
#include "server.h"
#include "client.h"
#include "msg_queue.h"
#include "command.h"
#include "string_parser.h"
#include "socket.h"

static int parse_port(int step, char *tmp, char *token, int *port)
{
    if (step != 4)
        return (-1);
    if (token != NULL)
        (*port) += atoi(token) * 256;
    if ((token = strsep(&tmp, ",")) != NULL)
        (*port) += atoi(token);
    if (token == NULL)
        return (-1);
    return (0);
}

static int parse_ip(char *cmd, char **ip, int *port)
{
    int stage = -1;
    char *tmp = strdup(cmd);
    char *token = NULL;

    while ((token = strsep(&tmp, ",")) != NULL && ++stage < 4) {
        if (stage == 0)
            sprintf(*ip, "%s.", token);
        else if (stage < 3)
            *ip = strcat(strcat(*ip, token), ".");
        else
            *ip = strcat(*ip, token);
    }
    return (parse_port(stage, tmp, token, port));
}

static void create_client_information(client_t *client, char *ip, int port)
{
    struct sockaddr_in new_in = create_socket_internet_address(port);
    struct in_addr ip_addr;

    client->dt_socket = create_socket();
    client->dt_mode = ACTIVE;
    inet_aton(ip, &ip_addr);
    new_in.sin_addr = ip_addr;
    client->dt_info = new_in;
}

void port(server_t *server, client_t *client, char *cmd)
{
    char *ip = malloc(sizeof(char) * 256);;
    int port = 0;

    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else {
        if (parse_ip(cmd, &ip, &port) == -1) {
            append_new_message(&client->write_queue, RESP_500);
            return;
        }
        create_client_information(client, ip, port);
        append_new_message(&client->write_queue, RESP_200);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}
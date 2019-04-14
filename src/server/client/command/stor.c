/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** PWD command functions
*/

#include <unistd.h>
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

static void store_file(client_t *client, int dsock, char *file)
{
    FILE *f = NULL;
    int pid = 0;
    char buf[2] = {0};

    if (chdir(client->path) == -1 || (f = fopen(file, "w+")) == NULL) {
        append_new_message(&client->write_queue, RESP_500);
        return;
    }
    pid = fork();
    if (pid == 0) {
        while ((read(dsock, buf, 1))) {
            buf[1] = '\0';
            fwrite(buf, 1, 1, f);
        }
        fclose(f);
        write(client->socket, "226 Done.\r\n", 11);
        exit(0);
    }
}

void stor(server_t *server, client_t *client, char *cmd)
{
    int dsock = 0;

    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else if (client->dt_mode != PASSIVE) {
        append_new_message(&client->write_queue, RESP_425);
    } else {
        append_new_message(&client->write_queue, RESP_150);
        dsock = accept_data(client);
        store_file(client, dsock, cmd);
        close(dsock);
        close(client->dt_socket);
        client->dt_mode = NOT_SET;
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}
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
        write(client->socket, RESP_500, strlen(RESP_500));
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

void stor(server_t *server, client_t *cl, char *cmd)
{
    int dsock = 0;

    if (is_connected(cl->user) == false) {
        append_new_message(&cl->write_queue, RESP_530_NEED_CONNECT);
    } else if (cl->dt_mode == NOT_SET) {
        append_new_message(&cl->write_queue, RESP_425);
    } else {
        append_new_message(&cl->write_queue, RESP_150);
        dsock = cl->dt_mode == ACTIVE ? connect_data(cl) : accept_data(cl);
        store_file(cl, cl->dt_mode == ACTIVE ? cl->dt_socket : dsock, cmd);
        cl->dt_mode == PASSIVE ? close(dsock) : 0;
        close(cl->dt_socket);
        cl->dt_mode = NOT_SET;
    }
    FD_SET(cl->socket, &server->sets[WRITING_SET]);
}
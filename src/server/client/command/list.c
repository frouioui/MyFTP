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

static void list_cur_dir(const int csock, const int sock, char *p)
{
    int pid = 0;
    char *cmd = NULL;
    int ofd = 0;

    pid = fork();
    if (pid == 0) {
        if (p == NULL) {
            write(csock, "226 Done.\r\n", 11);
            exit(0);
        }
        cmd = calloc(1, sizeof(char) * (strlen(p) + strlen("ls -la ") + 1));
        cmd = strcat(cmd, "ls -la ");
        cmd = strcat(cmd, p);
        ofd = dup(1);
        dup2(sock, 1);
        system(cmd);
        dup2(ofd, 1);
        write(csock, "226 Done.\r\n", 11);
        exit(0);
    }
}

void list(server_t *server, client_t *client, char *cmd)
{
    int dsock = 0;

    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else if (client->dt_mode != PASSIVE) {
        append_new_message(&client->write_queue, RESP_425);
    } else {
        if (check_file(check_path(client->parent_path, client->path, cmd))) {
            append_new_message(&client->write_queue, RESP_550_FILE);
        } else {
            write(client->socket, RESP_150, strlen(RESP_150));
            dsock = accept_data(client);
            list_cur_dir(client->socket, dsock,
                check_path(client->parent_path, client->path, cmd));
            close(dsock);
            close(client->dt_socket);
            client->dt_mode = NOT_SET;
        }
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}
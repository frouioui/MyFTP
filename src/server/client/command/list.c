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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "server.h"
#include "client.h"
#include "msg_queue.h"
#include "command.h"
#include "string_parser.h"
#include "socket.h"

int connect_data(client_t *client)
{
    int addrlen = sizeof(client->dt_info);
    int ret = connect(client->dt_socket, (struct sockaddr *)&client->dt_info,
            (socklen_t)addrlen);

    return (ret);
}

static void ls_dir(const int csock, const int sock, char *p)
{
    int pid = 0;
    char *cmd = NULL;
    int ofd = 0;

    pid = fork();
    if (pid == 0) {
        !p ? write(csock, "226 Done.\r\n", 11) : 0;
        !p ? exit(0) : 0;
        cmd = calloc(1, sizeof(char) * (strlen(p) + 30 + 1));
        cmd = strcat(cmd, "ls -l ");
        cmd = strcat(cmd, p);
        cmd = strcat(cmd , " | grep -v '^total'");
        ofd = dup(1);
        dup2(sock, 1);
        system(cmd);
        dup2(ofd, 1);
        write(csock, "226 Done.\r\n", 11);
        exit(0);
    }
}

void list(server_t *server, client_t *cl, char *cmd)
{
    int dsock = 0;

    if (is_connected(cl->user) == false) {
        append_new_message(&cl->write_queue, RESP_530_NEED_CONNECT);
    } else if (cl->dt_mode == NOT_SET) {
        append_new_message(&cl->write_queue, RESP_425);
    } else {
        if (check_file(check_path(cl->parent_path, cl->path, cmd))) {
            append_new_message(&cl->write_queue, RESP_550_FILE);
        } else {
            write(cl->socket, RESP_150, strlen(RESP_150));
            dsock = cl->dt_mode == ACTIVE ? connect_data(cl) : accept_data(cl);
            ls_dir(cl->socket, cl->dt_mode == ACTIVE ? cl->dt_socket : dsock,
                check_path(cl->parent_path, cl->path, cmd));
            cl->dt_mode == PASSIVE ? close(dsock) : 0;
            close(cl->dt_socket);
            cl->dt_mode = NOT_SET;
        }
    }
    FD_SET(cl->socket, &server->sets[WRITING_SET]);
}
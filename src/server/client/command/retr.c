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

int accept_data(client_t *client)
{
    int addrlen = sizeof(client->dt_info);
    int dsock = accept(client->dt_socket, (struct sockaddr *)&client->dt_info,
            (socklen_t *)&addrlen);

    return (dsock);
}

static void read_file_retr(const int f_fd, const int sock)
{
    int ret = 1;
    char c = 0;

    while (ret == 1) {
        ret = read(f_fd, &c, 1);
        if (ret == 1 && c == '\n') {
            write(sock, "\r\n", 2);
        } else if (ret == 1) {
            write(sock, &c, 1);
        }
    }
}

static void retreive_file(const int csock, const int dsock, const char *file)
{
    int pid = 0;
    int f_fd = 0;

    pid = fork();
    if (pid == 0) {
        if (file == NULL) {
            write(csock, "226 Done with error file NULL.\r\n", 32);
            exit(1);
        }
        f_fd = open(file, O_RDONLY);
        if (f_fd <= 0) {
            write(csock, "226 Done with error cant open file.\r\n", 37);
            exit(1);
        }
        read_file_retr(f_fd, dsock);
        write(csock, "226 Done.\r\n", 11);
        close(f_fd);
        exit(0);
    }
}

void retr(server_t *server, client_t *client, char *cmd)
{
    int dsock = 0;

    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else if (client->dt_mode != PASSIVE) {
        append_new_message(&client->write_queue, RESP_425);
    } else {
        if (!check_file(check_path(client->parent_path, client->path, cmd))) {
            append_new_message(&client->write_queue, RESP_550_FILE);
        } else {
            append_new_message(&client->write_queue, RESP_150);
            dsock = accept_data(client);
            retreive_file(client->socket, dsock,
                check_path(client->parent_path, client->path, cmd));
            close(dsock);
            close(client->dt_socket);
            client->dt_mode = NOT_SET;
        }
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}
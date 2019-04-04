/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Main file of the server function
*/

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "server.h"

static struct timeval create_timeout(void)
{
    struct timeval timeout = {0};

    timeout.tv_sec = 3 * 60;
    timeout.tv_usec = 0;
    return (timeout);
}

static void handle_client(server_t *server, const int cur_fd)
{
    if (cur_fd == server->socket) {
        // accept client
        // connect to it
        printf("Hello new client\n");
    } else {
        // run single client
        printf("Hello old client\n");
    }
}

static void which_client(server_t *server)
{
    for (unsigned int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &server->sets[WORKING_SET]) == true) {
            handle_client(server, i);
        }
    }
}

void server_start(server_t *server)
{
    struct timeval timeout = create_timeout();
    int ret = 0;

    while (true) {
        server->sets[WORKING_SET] = server->sets[READING_SET];
        ret = select(FD_SETSIZE, &server->sets[WORKING_SET], NULL, NULL,
            &timeout);
        if (ret == -1) {
            server->err = new_server_error(CONTINUE, strerror(errno));
        } else if (ret == 0) {
            // TODO: handle timeout ref: https://github.com/frouioui/MyFTP/issues/17
        } else {
            which_client(server);
        }
    }
}
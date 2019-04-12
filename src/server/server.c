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
#include "client.h"

static struct timeval create_timeout(void)
{
    struct timeval timeout = {0};

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;
    return (timeout);
}

void server_start(server_t *server)
{
    struct timeval timeout = create_timeout();
    int ret = 0;

    while (true) {
        server->sets[READWORK_SET] = server->sets[READING_SET];
        server->sets[WRITEWORK_SET] = server->sets[WRITING_SET];
        ret = select(FD_SETSIZE, &server->sets[READWORK_SET],
                                &server->sets[WRITEWORK_SET], NULL, NULL);
        if (ret == -1) {
            server->err = new_server_error(KEEP, strerror(errno));
        } else if (ret == 0) {
            // TODO: handle timeout ref: https://github.com/frouioui/MyFTP/issues/17
            (void)timeout;
        } else {
            handle_io(server);
        }
    }
}
/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Main file of the server function
*/

#include <sys/time.h>
#include <stdlib.h>
#include "server.h"

static struct timeval create_timeout(void)
{
    struct timeval timeout = {0};

    timeout.tv_sec = 3 * 60;
    timeout.tv_usec = 0;
    return (timeout);
}

void server_start(server_t *server)
{
    struct timeval timeout = create_timeout();
    int ret = 0;

    while (true) {
        server->sets[WORKING_SET] = server->sets[READING_SET];
        // TODO: Get to know how the writefds work
        ret = select(FD_SETSIZE, &server->sets[WORKING_SET], NULL, NULL,
            &timeout);
        (void)ret;

        break;
    }
}
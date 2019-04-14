/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Main I/O functions for client
*/

#include <stdlib.h>
#include "server.h"
#include "msg_queue.h"

void handle_io(void *server)
{
    server_t *srv = server;

    handle_read_client(srv);
    handle_write_client(srv);
}
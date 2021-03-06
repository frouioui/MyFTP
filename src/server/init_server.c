/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Initialization of the server
*/

#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "server.h"
#include "argument.h"

server_t init_server(const argument_t args)
{
    server_t server = {0};

    server.port = args.port;
    server.d_path = realpath(args.path, NULL);
    server.nb_client = 0;
    server.socket = -1;
    return (server);
}
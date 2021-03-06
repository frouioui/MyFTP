/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Connect a new client to the server
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "client.h"

client_t connect_new_client(void *server)
{
    server_t *srv = server;
    client_t new_client = {0};
    int addrlen = sizeof(srv->info);

    new_client.socket = accept(srv->socket, (struct sockaddr *)&srv->info,
            (socklen_t *)&addrlen);
    if (new_client.socket <= 0) {
        srv->err = new_server_error(KEEP, "could not connect the user");
        return (new_client);
    }
    new_client.path = strdup(srv->d_path);
    new_client.parent_path = strdup(srv->d_path);
    FD_SET(new_client.socket, &srv->sets[READING_SET]);
    return (new_client);
}
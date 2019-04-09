/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Add a client to the server
*/

#include <stdlib.h>
#include "server.h"
#include "client.h"

void add_client_to_server(server_t *server, const client_t client)
{
    server->clients = realloc(server->clients, sizeof(client_t) *
        (server->nb_client + 1));
    server->clients[server->nb_client] = client;
    server->nb_client++;
}
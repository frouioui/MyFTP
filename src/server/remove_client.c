/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Remove a client from the server
*/

#include "server.h"

static void move_clients(server_t *server, const int pos)
{
    while (pos + 1 < server->nb_client) {
        server->clients[pos] = server->clients[pos + 1];
    }
}

void server_remove_client(server_t *server, const int socket)
{
    for (int i = 0; i < server->nb_client; i++) {
        if (server->clients[i].socket == socket) {
            move_clients(server, i);
            server->nb_client--;
            break;
        }
    }
}

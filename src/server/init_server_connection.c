/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Initialization of the server connection
*/

#include "server.h"
#include "socket.h"

void init_server_connection(server_t *server)
{
    server->info = create_socket_internet_address(server->port);
    server->socket = create_socket();
    if (server->socket <= 0) {
        server->err = new_server_error(FATAL, "socket creation error");
    }
    if (bind_socket(server->socket, &server->info, false) < 0) {
        server->err = new_server_error(FATAL, "bind socket error");
        return;
    }
    if (listen_socket(server->socket, MAXIMUM_PENDING_CONNECTION) < 0) {
        server->err = new_server_error(FATAL, "listen error");
    }
}
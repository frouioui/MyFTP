/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Manage the server error
*/

#include <string.h>
#include "server.h"

server_error_t new_server_error(server_error_type_t type, char *message)
{
    server_error_t err;

    err.err_type = type;
    err.msg = strdup(message);
    return (err);
}
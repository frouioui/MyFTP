/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Command include file
*/

#if !defined(_COMMAND_H)
#define _COMMAND_H

#include "server.h"
#include "client.h"

struct cmd_function_s {
    char *cmd;
    void (*exec)(server_t *, client_t *);
};

typedef struct cmd_function_s cmd_function_t;

void execute_last_command(server_t *server, client_t *client);

void user_login(server_t *server, client_t *client);
void user_password(server_t *server, client_t *client);

#endif // _COMMAND_H

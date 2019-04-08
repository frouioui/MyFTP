/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Execute the last command that a client got
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "client.h"
#include "msg_queue.h"
#include "command.h"
#include "string_parser.h"

static void analyse_command(server_t *server, client_t *client,
    const char *cmd)
{
    cmd_function_t cmd_func[3] = {{"user", user_login},
        {"pass", user_password}, {"quit", user_quit}};
    char *tmp = strdup(cmd);

    str_to_lower_case(tmp);
    for (unsigned int i = 0; i < 3; i++) {
        if (strncmp(cmd_func[i].cmd, tmp, strlen(cmd_func[i].cmd)) == 0) {
            cmd_func[i].exec(server, client,
                strdup(cmd + (strlen(cmd_func[i].cmd) + 1)));
            break;
        }
    }
    free(tmp);
}

void execute_last_command(server_t *server, client_t *client)
{
    char *cmd = get_whole_first_message(&client->read_queue);

    analyse_command(server, client, cmd);
    free(cmd);
}
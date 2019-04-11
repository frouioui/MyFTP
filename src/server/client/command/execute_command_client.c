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

static void unknown_command(server_t *server, client_t *client)
{

    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else {
        append_new_message(&client->write_queue, RESP_500);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}

static void analyse_command(server_t *server, client_t *client, char *cmd)
{
    cmd_function_t cmd_func[8] = {{"user", user_login},
        {"pass", user_password}, {"quit", user_quit}, {"noop", noop_user},
        {"help", help_user}, {"cdup", cdup_user}, {"cwd", cwd_user},
        {"pwd", pwd_user}};
    char *tmp = strdup(cmd);
    bool execed = false;

    str_to_lower_case(tmp);
    trim_str(cmd, "\r\n");
    for (unsigned int i = 0; i < 8; i++) {
        if (strncmp(cmd_func[i].cmd, tmp, strlen(cmd_func[i].cmd)) == 0) {
            cmd_func[i].exec(server, client,
                strdup(cmd + (strlen(cmd_func[i].cmd) + 1)));
            execed = true;
            break;
        }
    }
    (execed == false) ? (unknown_command(server, client)) : (0);
    free(tmp);
}

void execute_last_command(server_t *server, client_t *client)
{
    char *cmd = get_whole_first_message(&client->read_queue);

    // TODO: remove all extra space and tab
    analyse_command(server, client, cmd);
    free(cmd);
}
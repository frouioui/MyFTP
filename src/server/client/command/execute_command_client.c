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

static char *get_client_command(client_t *client)
{
    char *cmd = NULL;
    char *buf = NULL;

    if (client->read_queue.nb_msg == 0)
        return (NULL);
    cmd = malloc(sizeof(char) * 1);
    cmd[0] = 0;
    while (is_message_done(cmd, client->write_queue.end_of_msg) == false) {
        buf = read_and_trim_last_message(&client->read_queue, 1);
        if (buf == NULL)
            return (cmd);
        cmd = realloc(cmd, sizeof(char) * (strlen(cmd) + strlen(buf) + 1));
        if (cmd == NULL)
            return (NULL);
        cmd = strcat(cmd, buf);
    }
    return (cmd);
}

static void analyse_command(server_t *server, client_t *client,
    const char *cmd)
{
    cmd_function_t cmd_func[2] = {{"USER", user_login},
        {"PASS", user_password}};

    for (unsigned int i = 0; i < 2; i++) {
        if (strcmp(cmd_func[i].cmd, cmd) == 0) {
            cmd_func[i].exec(server, client,
                strdup(cmd + (strlen(cmd_func[i].cmd) + 1)));
            break;
        }
    }
}

void execute_last_command(server_t *server, client_t *client)
{
    char *cmd = get_client_command(client);

    analyse_command(server, client, cmd);
    free(cmd);
}
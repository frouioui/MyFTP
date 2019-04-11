/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Source file of the CDW command
*/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "server.h"
#include "client.h"
#include "msg_queue.h"
#include "command.h"
#include "string_parser.h"

static bool is_path_dir(const char *path)
{
    struct stat path_stat;

    stat(path, &path_stat);
    return !S_ISREG(path_stat.st_mode);
}

static char *handle_path_operation(char *cmd, char *root, char *root_2)
{
    char *buf = NULL;

    if (cmd[0] == '/') {
        buf = calloc(1, sizeof(char) * (strlen(root) + strlen(root_2) +
            strlen(cmd) + 1));
        buf = strcat(buf, root);
        buf = strcat(buf, cmd);
        cmd = strdup(buf);
    } else {
        buf = calloc(1, sizeof(char) * (strlen(cmd) + 2 + strlen(root_2)));
        buf = strcat(buf, root_2);
        buf = strcat(buf, "/");
        buf = strcat(buf, cmd);
        cmd = strdup(buf);
    }
    free(buf);
    return (cmd);
}

static char *check_path(char *root, char *root_2, char *cmd)
{
    char *new_path = NULL;
    char *buf = NULL;

    cmd[0] == 0 ? strcpy(cmd, root_2) : 0;
    root_2 = realpath(root_2[0] == '/' ? root_2 + 1 : root_2, NULL);
    root = realpath(root, NULL);
    cmd = handle_path_operation(cmd, root, root_2);
    new_path = realpath(cmd, NULL);
    if (!new_path)
        return (NULL);
    if (strncmp(new_path, root_2, strlen(root)))
        return (root);
    return (new_path);
}

static char *clear_path_client(char *root, char *path)
{
    char *new = calloc(1, sizeof(char) * (strlen(root) + strlen(path) + 1));
    int a = 0;

    for (unsigned int i = strlen(root); i < strlen(path) && path[i]; i++) {
        new[a++] = path[i];
        new[a] = '\0';
    }
    free(path);
    return (new);
}

void cwd_user(server_t *server, client_t *client, char *cmd)
{
    char *new_p = NULL;
    char *par = NULL;

    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else {
        new_p = check_path(client->parent_path, client->path, strdup(cmd));
        if (new_p == NULL || is_path_dir(new_p) == false) {
            append_new_message(&client->write_queue, RESP_550);
            free(new_p);
            return;
        }
        par = realpath(client->parent_path, NULL);
        new_p = clear_path_client(par, new_p);
        free(client->path);
        client->path = strlen(new_p) != 0 ? new_p : strdup(client->parent_path);
        append_new_message(&client->write_queue, RESP_250);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}
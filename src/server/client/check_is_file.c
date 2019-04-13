/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Check if the given path is a file or not
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

bool check_file(const char *path)
{
    struct stat path_stat;

    if (path == NULL) {
        return (false);
    }
    if (stat(path, &path_stat) == -1)
        return (false);
    if (S_ISREG(path_stat.st_mode))
        return (true);
    return (false);
}
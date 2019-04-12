/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** The main argument parsing file
*/

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "argument.h"
#include "string_parser.h"

static bool is_helper_flag(char *flag)
{
    if (strcmp(flag, "-h") == 0 || strcmp(flag, "--help") == 0
        || strcmp(flag, "-help") == 0) {
        return (true);
    }
    return (false);
}

static bool is_path_dir(const char *path)
{
    struct stat path_stat;

    stat(path, &path_stat);
    return !S_ISREG(path_stat.st_mode);
}

argument_t parse_argument(int argc, char *argv[])
{
    argument_t args = {helper: false, valid: false, port: 21, path: ""};

    if (argc == 2 && is_helper_flag(argv[1]) == true) {
        args.helper = true;
        args.valid = true;
    } else if (argc == 3 && is_number(argv[1]) == true) {
        args.port = atoi(argv[1]);
        args.path = strdup(argv[2]);
        if (is_path_dir(args.path) == false) {
            args.valid = false;
        } else {
            args.valid = true;
        }
    }
    return (args);
}
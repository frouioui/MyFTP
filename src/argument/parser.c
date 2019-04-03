/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** The main argument parsing file
*/

#include <string.h>
#include <stdlib.h>
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

argument_t parse_argument(int argc, char *argv[])
{
    argument_t args = {helper: false, valid: false, port: 21, path: ""};

    if (argc == 2 && is_helper_flag(argv[1]) == true) {
        args.helper = true;
        args.valid = true;
    } else if (argc == 3 && is_number(argv[1]) == true) {
        args.port = atoi(argv[1]);
        args.path = strdup(argv[2]);
        args.valid = true;
    }
    return (args);
}
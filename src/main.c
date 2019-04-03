/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Main file containing the main function
*/

#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "argument.h"
#include "core.h"

int main(int argc, char *argv[])
{
    server_t server = {0};
    argument_t args = parse_argument(argc, argv);

    if (args.valid == false || args.path == NULL) {
        puts("Invalid argument, try --help option.");
        return (FAILURE);
    } else if (args.helper == true) {
        print_helper();
        return (SUCCESS);
    }
    server = init_server(args);
    init_server_connection(&server);
    return (SUCCESS);
}
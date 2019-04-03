/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Main file containing the main function
*/

#include <stdlib.h>
#include <stdio.h>
#include "argument.h"
#include "core.h"

int main(int argc, char *argv[])
{
    argument_t args = parse_argument(argc, argv);

    if (args.valid == false || args.path == NULL) {
        puts("Invalid argument, try --help option.");
        return (FAILURE);
    } else if (args.helper == true) {
        print_helper();
        return (SUCCESS);
    }
    return (SUCCESS);
}
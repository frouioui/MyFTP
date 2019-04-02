/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Main file containing the main function
*/

#include "argument.h"
#include "core.h"

int main(int argc, char *argv[])
{
    argument_t args = parse_argument(argc, argv);

    if (args.valid == false) {
        // TODO: Display error message or helper
        return (EXIT_FAILURE);
    } else if (args.helper == true) {
        // TODO: Display helper
        return (EXIT_SUCCESS);
    }
    return (EXIT_SUCCESS);
}
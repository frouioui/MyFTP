/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Test file of the argument parser functions
*/

#include <criterion/criterion.h>
#include "argument.h"

Test(argument_parser, no_argument)
{
    argument_t args = {};
    int argc = 1;
    char **argv = malloc(sizeof(char *) * (argc + 1));

    argv[0] = strdup("myftp");
    argv[1] = NULL;
    args = parse_argument(argc, argv);
    cr_assert_eq(args.valid, false);
}

Test(argument_parser, helper_argument)
{
    argument_t args = {};
    int argc = 2;
    char **argv = malloc(sizeof(char *) * (argc + 1));

    argv[0] = strdup("myftp");
    argv[1] = strdup("-h");
    argv[2] = NULL;
    args = parse_argument(argc, argv);
    cr_assert_eq(args.valid, true);
    cr_assert_eq(args.helper, true);
}

Test(argument_parser, regular_argument)
{
    argument_t args = {};
    int argc = 3;
    char **argv = malloc(sizeof(char *) * (argc + 1));

    argv[0] = strdup("myftp");
    argv[1] = strdup("8888");
    argv[2] = strdup("./directory");
    argv[3] = NULL;
    args = parse_argument(argc, argv);
    cr_assert_eq(args.valid, true);
    cr_assert_eq(args.helper, false);
    cr_assert_eq(args.port, 8888);
    cr_assert_str_eq(args.path, "./directory");
}

Test(argument_parser, not_a_port)
{
    argument_t args = {};
    int argc = 3;
    char **argv = malloc(sizeof(char *) * (argc + 1));

    argv[0] = strdup("myftp");
    argv[1] = strdup("toto");
    argv[2] = strdup("./directory");
    argv[3] = NULL;
    args = parse_argument(argc, argv);
    cr_assert_eq(args.valid, false);
}
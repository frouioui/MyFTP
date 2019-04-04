/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Test file of the init_server function
*/

#include <criterion/criterion.h>
#include "server.h"
#include "argument.h"

Test(init_server, check_values)
{
    argument_t args = {port: 42, path: "toto", helper: false, valid: true};
    server_t server = {0};

    server = init_server(args);
    cr_assert_eq(server.port, args.port);
    cr_assert_str_eq(server.d_path, "toto");
    cr_assert_eq(server.nb_client, 0);
    cr_assert_eq(server.socket, -1);
}
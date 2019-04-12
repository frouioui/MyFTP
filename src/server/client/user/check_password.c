/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Check if the password and the username are correct
*/

#include <string.h>
#include <stdlib.h>
#include "user.h"
#include "string_parser.h"

bool pass_and_user_valid(const user_t user)
{
    char *name = strdup(user.name);

    str_to_lower_case(name);
    if (strcmp(name, "anonymous") == 0) {
        free(name);
        return (true);
    }
    free(name);
    return (false);
}
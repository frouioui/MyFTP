/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Check if the password and the username are correct
*/

#include <string.h>
#include "user.h"

bool pass_and_user_valid(const user_t user)
{
    if (strcmp(user.name, "anonymous") == 0) {
        return (true);
    }
    return (false);
}
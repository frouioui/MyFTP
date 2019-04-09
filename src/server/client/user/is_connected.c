/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Check if the user is connected or not
*/

#include <stdlib.h>
#include <stdbool.h>
#include "user.h"

bool is_connected(user_t user)
{
    if (user.name != NULL && user.pass != NULL) {
        if (pass_and_user_valid(user) == true) {
            return (true);
        }
    }
    return (false);
}
/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Check if the given string only contain number/digit
*/

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool is_number(char *str)
{
    if (str == NULL)
        return (false);
    for (unsigned int i = 0; str[i]; i++) {
        if (isdigit(str[i]) == false)
            return (false);
    }
    return (true);
}
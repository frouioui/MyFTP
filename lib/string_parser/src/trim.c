/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Trim a strin
*/

#include <stdlib.h>
#include <string.h>

void trim_str(char *str, const char *to_trim)
{
    if (str == NULL || to_trim == NULL)
        return;
    for (unsigned int i = 0; str[i]; i++) {
        if (strcmp(str + i, to_trim) == 0) {
            str[i] = '\0';
            break;
        }
    }
}
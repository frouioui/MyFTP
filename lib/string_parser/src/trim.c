/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Trim a strin
*/

#include <stdlib.h>
#include <string.h>

static void remove_end(char *str, const int size)
{
    for (int i = 0; i < size; i++) {
        str[i] = '\0';
    }
}

void trim_str(char *str, const char *to_trim)
{
    if (str == NULL || to_trim == NULL)
        return;
    for (unsigned int i = 0; str[i]; i++) {
        if (strcmp(str + i, to_trim) == 0) {
            remove_end(str + i, strlen(to_trim));
            break;
        }
    }
}
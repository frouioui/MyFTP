/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Put the string to lowercase
*/

#include <ctype.h>

void str_to_lower_case(char *str)
{
    for (unsigned int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
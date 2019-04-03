/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Definition of the user_t struct and functions
*/

#if !defined(_USER_H)
#define _USER_H

#include <stdbool.h>

struct user_s {
    char *name;
    char *pass;
    bool connected;
};

typedef struct user_s user_t;

#endif // _USER_H

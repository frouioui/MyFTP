/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Argument functions and structs
*/

#if !defined(_ARGUMENT_H)
#define _ARGUMENT_H

#include <stdbool.h>

struct argument_s {
    int port;
    char *path;
    bool helper;
    bool valid;
};

typedef struct argument_s argument_t;

argument_t parse_argument(int argc, char *argv[]);

#endif // _ARGUMENT_H

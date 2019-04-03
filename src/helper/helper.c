/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Helper function
*/

#include <stdio.h>

void print_helper(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("\tport\tis the port number on which the server socket listens\n");
    printf("\tpath\tis the path to the home directory for the anonymous"\
        "user\n");
}
/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Check if the message is done or not
*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_message_done(const char *msg, const char *end_of_msg)
{
    size_t len_msg = strlen(msg);
    size_t len_end_of_msg = strlen(end_of_msg);

    if (len_msg <= len_end_of_msg)
        return (false);
    return (strncmp(msg + len_msg - len_end_of_msg
                    , end_of_msg, len_end_of_msg) == 0);
}
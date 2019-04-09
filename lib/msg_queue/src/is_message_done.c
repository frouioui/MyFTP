/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Check if the message is done or not
*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "msg_queue.h"

bool is_message_done(const char *msg, const char *end_of_msg)
{
    size_t len_msg = strlen(msg);
    size_t len_end_of_msg = strlen(end_of_msg);

    if (len_msg <= len_end_of_msg)
        return (false);
    return (strncmp(msg + len_msg - len_end_of_msg
                    , end_of_msg, len_end_of_msg) == 0);
}

bool is_last_message_done(message_queue_t *msg_queue)
{
    if (msg_queue->nb_msg == 0)
        return (false);
    return (is_message_done(msg_queue->msg[msg_queue->nb_msg - 1],
        msg_queue->end_of_msg));
}
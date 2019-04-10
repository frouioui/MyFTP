/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Destroy the given message queue
*/

#include <stdlib.h>
#include "msg_queue.h"

void destroy_message_queue(message_queue_t *msg_queue)
{
    for (unsigned int i = 0; i < msg_queue->nb_msg && msg_queue->msg[i]; i++) {
        free(msg_queue->msg[i]);
    }
    free(msg_queue->msg);
    free(msg_queue->end_of_msg);
}
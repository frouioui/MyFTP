/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Append a new message to the queue
*/

#include <stdlib.h>
#include <stdbool.h>
#include "msg_queue.h"

void append_new_message(message_queue_t *msg_queue, char *msg)
{
    for (unsigned int i = 0; i < msg_queue->nb_msg && msg_queue->msg[i]; i++) {
        if (is_message_done(msg_queue->msg[i]) == false) {
            // TODO: append
            return;
        }
    }
    // TODO: append a new "char *" to msg_queue->msg contianing "char* msg"
}
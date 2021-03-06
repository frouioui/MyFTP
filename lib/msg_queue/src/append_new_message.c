/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Append a new message to the queue
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "msg_queue.h"

void append_new_message(message_queue_t *msg_queue, char *msg)
{
    for (unsigned int i = 0; i < msg_queue->nb_msg && msg_queue->msg[i]; i++) {
        if (!is_message_done(msg_queue->msg[i], msg_queue->end_of_msg)) {
            msg_queue->msg[i] = realloc(msg_queue->msg[i], sizeof(char) *
                (strlen(msg_queue->msg[i]) + strlen(msg) + 2));
            msg_queue->msg[i] = strcat(msg_queue->msg[i], msg);
            return;
        }
    }
    msg_queue->msg = realloc(msg_queue->msg, sizeof(char *) *
        (msg_queue->nb_msg + 2));
    if (msg_queue->msg == NULL)
        exit(1);
    msg_queue->msg[msg_queue->nb_msg] = strdup(msg);
    msg_queue->msg[msg_queue->nb_msg + 1] = NULL;
    msg_queue->nb_msg++;
}
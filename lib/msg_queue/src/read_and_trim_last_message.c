/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** read a queue of n size and trim it
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "msg_queue.h"

static bool end_msg(const char *end, const char *msg)
{
    return (strncmp(end, msg, strlen(end)) == 0);
}

static void trim_first_message(message_queue_t *msg_queue)
{
    char **new_msg = NULL;
    void *buf = NULL;

    if (msg_queue->nb_msg == 0)
        return;
    new_msg = malloc(sizeof(char *) * (msg_queue->nb_msg));
    memset(new_msg, 0, (sizeof(char *) * (msg_queue->nb_msg)));
    free(msg_queue->msg[0]);
    for (unsigned int i = 1; i < msg_queue->nb_msg && msg_queue->msg[i]; i++) {
        new_msg[i - 1] = strdup(msg_queue->msg[i]);
        free(msg_queue->msg[i]);
    }
    buf = msg_queue->msg;
    msg_queue->msg = new_msg;
    free(buf);
}

char *read_and_trim_last_message(message_queue_t *msg_queue,
    const unsigned int size)
{
    unsigned int i = 0;
    char *ret = NULL;
    char *msg = msg_queue->msg[0];

    if (msg_queue->nb_msg == 0 || size == 0)
        return (NULL);
    ret = malloc(sizeof(char) * (strlen(msg) + 1));
    memset(ret, 0, strlen(msg) + 1);
    while (i < size && msg[i] && end_msg(msg_queue->end_of_msg, msg + i)) {
        ret[i] = msg[i];
    }
    if (is_message_done(ret, msg_queue->end_of_msg) == true) {
        trim_first_message(msg_queue);
    }
    return (ret);
}
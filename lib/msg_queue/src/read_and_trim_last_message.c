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

static void trim_first_message(message_queue_t *msg_queue)
{
    char **new_msg = NULL;
    void *buf = NULL;

    if (msg_queue->nb_msg == 0)
        return;
    new_msg = malloc(sizeof(char *) * (msg_queue->nb_msg));
    memset(new_msg, 0, (sizeof(char *) * (msg_queue->nb_msg)));
    free(msg_queue->msg[0]);
    msg_queue->msg[0] = NULL;
    for (unsigned int i = 1; i < msg_queue->nb_msg && msg_queue->msg[i]; i++) {
        new_msg[i - 1] = strdup(msg_queue->msg[i]);
        free(msg_queue->msg[i]);
    }
    msg_queue->nb_msg--;
    buf = msg_queue->msg;
    msg_queue->msg = new_msg;
    free(buf);
}

static void move_char_left(char *str)
{
    unsigned int i = 0;

    while (str[i] && str[i + 1]) {
        str[i] = str[i + 1];
        i++;
    }
    str[i] = 0;
}

char *read_and_trim_last_message(message_queue_t *msg_queue,
    const unsigned int size)
{
    unsigned int i = 0;
    char *ret = NULL;
    char *msg = msg_queue->msg[0];

    if (msg_queue->nb_msg == 0 || size == 0 || strlen(msg_queue->msg[0]) == 0)
        return (NULL);
    ret = malloc(sizeof(char) * (strlen(msg) + 1));
    memset(ret, 0, strlen(msg) + 1);
    while (i < size && msg[0] &&
        !is_message_done(ret, msg_queue->end_of_msg)) {
        ret[i] = msg[0];
        move_char_left(msg);
        i++;
    }
    if (is_message_done(ret, msg_queue->end_of_msg) == true) {
        trim_first_message(msg_queue);
    }
    return (ret);
}
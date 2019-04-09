/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Creation of a message queue
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "msg_queue.h"

message_queue_t create_message_queue(char *end_of_message)
{
    message_queue_t msg_queue = {0};

    msg_queue.msg = malloc(sizeof(char *) * 1);
    if (msg_queue.msg == NULL) {
        puts("Error in create_message_queue: malloc failed.");
        exit(1);
    }
    msg_queue.msg[0] = NULL;
    msg_queue.end_of_msg = strdup(end_of_message);
    return (msg_queue);
}
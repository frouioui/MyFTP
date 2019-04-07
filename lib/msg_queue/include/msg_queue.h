/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** include file of the message queue library
*/

#if !defined(_MSG_QUEUE_H)
#define _MSG_QUEUE_H

#include <stdbool.h>

struct message_queue {
    char **msg;
    unsigned int nb_msg;
    char *end_of_msg;
};

typedef struct message_queue message_queue_t;

message_queue_t create_message_queue(char *end_of_message);
bool is_message_done(const char *msg, const char *end_of_msg);
void destroy_message_queue(message_queue_t *msg_queue);
char *read_and_trim_last_message(message_queue_t *msg_queue, const
    unsigned int size);
void append_new_message(message_queue_t *msg_queue, char *msg);
bool is_last_message_done(message_queue_t *msg_queue);
char *get_whole_first_message(message_queue_t *msg_queue);

#endif // _MSG_QUEUE_H

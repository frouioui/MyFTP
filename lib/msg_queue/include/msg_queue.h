/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** include file of the message queue library
*/

#if !defined(_MSG_QUEUE_H)
#define _MSG_QUEUE_H

struct message_queue {
    char **msg;
    unsigned int nb_msg;
    char *end_of_msg;
};

typedef struct message_queue message_queue_t;

message_queue_t create_message_queue(char *end_of_message);
bool is_message_done(const char *msg, const char *end_of_msg);

#endif // _MSG_QUEUE_H

/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Init the client's queues
*/

#include "client.h"
#include "msg_queue.h"

void init_client_queues(client_t *client)
{
    client->read_queue = create_message_queue("\n\r");
    client->write_queue = create_message_queue("\n\r");
}
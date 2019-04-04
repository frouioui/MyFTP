/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Test file of the create_msg_queue functions
*/

#include <criterion/criterion.h>
#include "msg_queue.h"

Test(create_msg_queue, check_values)
{
    message_queue_t msg_queue = create_message_queue("\n\r");

    cr_assert_not_null(msg_queue.msg);
    cr_assert_null(msg_queue.msg[0]);
    cr_assert_eq(msg_queue.nb_msg, 0);
    cr_assert_str_eq(msg_queue.end_of_msg, "\n\r");
}
/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Test file of the append_new_message function
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "msg_queue.h"

Test(append_new_message, append_to_empty_queue)
{
    message_queue_t msg_queue = create_message_queue("\n\r");

    append_new_message(&msg_queue, "203 cancel\n\r");
    cr_assert_not_null(msg_queue.msg[0]);
    cr_assert_str_eq(msg_queue.msg[0], "203 cancel\n\r");
    cr_assert_eq(msg_queue.nb_msg, 1);
}

Test(append_new_message, append_to_a_non_empty_queue)
{
    message_queue_t msg_queue = create_message_queue("\n\r");

    append_new_message(&msg_queue, "203 cancel\n\r");
    append_new_message(&msg_queue, "505 other\n\r");
    cr_assert_not_null(msg_queue.msg[0]);
    cr_assert_not_null(msg_queue.msg[1]);
    cr_assert_str_eq(msg_queue.msg[0], "203 cancel\n\r");
    cr_assert_str_eq(msg_queue.msg[1], "505 other\n\r");
    cr_assert_eq(msg_queue.nb_msg, 2);
}

Test(append_new_message, append_unfinished_message)
{
    message_queue_t msg_queue = create_message_queue("\n\r");

    append_new_message(&msg_queue, "203 cancel");
    cr_assert_not_null(msg_queue.msg[0]);
    cr_assert_str_eq(msg_queue.msg[0], "203 cancel");
    cr_assert_eq(msg_queue.nb_msg, 1);
}

Test(append_new_message, finish_unfinished_message)
{
    message_queue_t msg_queue = create_message_queue("\n\r");

    append_new_message(&msg_queue, "203 canc");
    append_new_message(&msg_queue, "el\n\r");
    cr_assert_not_null(msg_queue.msg[0]);
    cr_assert_str_eq(msg_queue.msg[0], "203 cancel\n\r");
    cr_assert_eq(msg_queue.nb_msg, 1);
}

Test(append_new_message, append_multiple_message)
{
    message_queue_t msg_queue = create_message_queue("\n\r");

    append_new_message(&msg_queue, "203 canc");
    append_new_message(&msg_queue, "el\n\r");
    append_new_message(&msg_queue, "toto\n\r");
    append_new_message(&msg_queue, "val");
    append_new_message(&msg_queue, "grind\n\r");
    cr_assert_not_null(msg_queue.msg[0]);
    cr_assert_not_null(msg_queue.msg[1]);
    cr_assert_not_null(msg_queue.msg[2]);
    cr_assert_str_eq(msg_queue.msg[0], "203 cancel\n\r");
    cr_assert_str_eq(msg_queue.msg[1], "toto\n\r");
    cr_assert_str_eq(msg_queue.msg[2], "valgrind\n\r");
    cr_assert_eq(msg_queue.nb_msg, 3);
}
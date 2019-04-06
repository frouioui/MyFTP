/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** read_and_trim_last_message test functions
*/

#include <criterion/criterion.h>
#include "msg_queue.h"

Test(read_and_trim_last_message, read_one_byte)
{
    message_queue_t msg_queue = create_message_queue("\n\r");
    char *buf = NULL;

    append_new_message(&msg_queue, "203 cancel\n\r");
    cr_assert_not_null(msg_queue.msg[0]);
    cr_assert_str_eq(msg_queue.msg[0], "203 cancel\n\r");
    cr_assert_eq(msg_queue.nb_msg, 1);
    buf = read_and_trim_last_message(&msg_queue, 1);
    cr_assert_str_eq(buf, "2");
}

Test(read_and_trim_last_message, read_two_byte)
{
    message_queue_t msg_queue = create_message_queue("\n\r");
    char *buf = NULL;

    append_new_message(&msg_queue, "203 cancel\n\r");
    cr_assert_not_null(msg_queue.msg[0]);
    cr_assert_str_eq(msg_queue.msg[0], "203 cancel\n\r");
    cr_assert_eq(msg_queue.nb_msg, 1);
    buf = read_and_trim_last_message(&msg_queue, 2);
    cr_assert_str_eq(buf, "20");
}

Test(read_and_trim_last_message, read_whole)
{
    message_queue_t msg_queue = create_message_queue("\n\r");
    char *buf = NULL;

    append_new_message(&msg_queue, "203 cancel\n\r");
    cr_assert_not_null(msg_queue.msg[0]);
    cr_assert_str_eq(msg_queue.msg[0], "203 cancel\n\r");
    cr_assert_eq(msg_queue.nb_msg, 1);
    buf = read_and_trim_last_message(&msg_queue, 12);
    cr_assert_str_eq(buf, "203 cancel\n\r");
    cr_assert_eq(msg_queue.nb_msg, 0);
    cr_assert_null(msg_queue.msg[0]);
}

Test(read_and_trim_last_message, nothing_to_read)
{
    message_queue_t msg_queue = create_message_queue("\n\r");
    char *buf = NULL;

    append_new_message(&msg_queue, "203 cancel\n\r");
    cr_assert_not_null(msg_queue.msg[0]);
    cr_assert_str_eq(msg_queue.msg[0], "203 cancel\n\r");
    cr_assert_eq(msg_queue.nb_msg, 1);
    buf = read_and_trim_last_message(&msg_queue, 12);
    cr_assert_str_eq(buf, "203 cancel\n\r");
    cr_assert_eq(msg_queue.nb_msg, 0);
    cr_assert_null(msg_queue.msg[0]);
    buf = read_and_trim_last_message(&msg_queue, 34);
    cr_assert_eq(buf, NULL);
}

Test(read_and_trim_last_message, trim_multiple_msg)
{
    message_queue_t msg_queue = create_message_queue("\n\r");
    char *buf = NULL;

    append_new_message(&msg_queue, "203 cancel\n\r");
    append_new_message(&msg_queue, "503 error\n\r");
    append_new_message(&msg_queue, "NOOP\n\r");
    buf = read_and_trim_last_message(&msg_queue, 12);
    cr_assert_str_eq(buf, "203 cancel\n\r");
    cr_assert_eq(msg_queue.nb_msg, 2);
    cr_assert_not_null(msg_queue.msg[0]);
    cr_assert_not_null(msg_queue.msg[1]);
    cr_assert_null(msg_queue.msg[2]);
}
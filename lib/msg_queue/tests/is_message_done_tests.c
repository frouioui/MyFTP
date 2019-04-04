/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Test file of the is_message_done function
*/

#include <criterion/criterion.h>
#include "msg_queue.h"

Test(is_message_done, done_message)
{
    cr_assert_eq(is_message_done("203 live\n\r", "\n\r"), true);
}

Test(is_message_done, not_done_message)
{
    cr_assert_eq(is_message_done("203 live toto", "\n\r"), false);
}

Test(is_message_done, msg_smaller_than_end)
{
    cr_assert_eq(is_message_done("o", "\n\r"), false);
}

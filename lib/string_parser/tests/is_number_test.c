/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Test file of the is_number function
*/

#include <criterion/criterion.h>
#include <string.h>
#include "string_parser.h"

Test(is_number, only_digit)
{
    char *str = strdup("1234567890");

    cr_assert_eq(is_number(str), true);
    free(str);
}

Test(is_number, only_char)
{
    char *str = strdup("wfijewowiwd");

    cr_assert_eq(is_number(str), false);
    free(str);
}

Test(is_number, mixed_digit_char)
{
    char *str = strdup("wfi23je2wow2i2w4d5");

    cr_assert_eq(is_number(str), false);
    free(str);
}
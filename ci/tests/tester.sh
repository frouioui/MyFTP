#!/usr/bin/env bash

function display_test_name()
{
    echo "[TEST] $1"
}

function test_wrong_args()
{
    display_test_name "test_wrong_args"
    ./myftp > /dev/null
    if [ $? -eq 84 ]
    then
        echo -e "\t[PASSED]"
    else
        echo -e "\t[FAILED]"
        exit 1
    fi
}

function main()
{
    test_wrong_args
}

main
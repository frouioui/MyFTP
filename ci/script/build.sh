#!/usr/bin/env bash

cd $APPLICATION_DIRECTORY_DOCKER

make fclean

make

make clean

make re

make myftp
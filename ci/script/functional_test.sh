#!/usr/bin/env bash

chmod +x ./ci/tests/tester.
make
echo -e "\nBEGIN TEST\n"
./ci/tests/tester.sh
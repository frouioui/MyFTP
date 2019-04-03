#!/usr/bin/env bash

ssh-keyscan git.epitech.eu >> ~/.ssh/known_hosts
git checkout $TRAVIS_BRANCH
git push --repo=git@git.epitech.eu:/florent.poinsard@epitech.eu/NWP_myftp_2018 --force
#!/bin/bash

if [ "$1" = "release" ]
then
    ./build/release/mc-one-week-challenge
else
    ./build/debug/mc-one-week-challenge
fi
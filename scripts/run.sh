#!/bin/bash

if [ "$1" = "release" ]
then
    ./build/release/minecraft-one-week-challenge
else
    ./build/debug/minecraft-one-week-challenge
fi
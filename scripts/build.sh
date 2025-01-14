#!/bin/bash

target_release() {
    cd release
    cmake -DCMAKE_BUILD_TYPE=Release ../..
    make
    echo "Built target in build/release/"
    cd ../..
}

target_debug() {
    cd debug 
    cmake -DCMAKE_BUILD_TYPE=Debug ../..
    make
    echo "Built target in build/debug/"
    cd ../..
}

# Create folder for distribution
if [ "$1" = "release" ]
then
    if [ -d "$mc-one-week-challenge" ]
    then
        rm -rf -d mc-one-week-challenge
    fi

    mkdir -p mc-one-week-challenge
fi

# Creates the folder for the buildaries
mkdir -p mc-one-week-challenge 
mkdir -p mc-one-week-challenge/assets
mkdir -p build
mkdir -p build/release
mkdir -p build/debug
cd build

# Builds target
if [ "$1" = "release" ]
then
    target_release
    cp build/release/mc-one-week-challenge mc-one-week-challenge/mc-one-week-challenge
else
    target_debug
fi

cp -R assets mc-one-week-challenge/

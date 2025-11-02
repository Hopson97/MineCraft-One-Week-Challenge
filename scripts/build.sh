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
    if [ -d "$minecraft-one-week-challenge" ]
    then
        rm -rf -d minecraft-one-week-challenge
    fi

    mkdir -p minecraft-one-week-challenge
fi

# Creates the folder for the buildaries
mkdir -p minecraft-one-week-challenge 
mkdir -p minecraft-one-week-challenge/assets
mkdir -p build
mkdir -p build/release
mkdir -p build/debug
cd build

# Builds target
if [ "$1" = "release" ]
then
    target_release
    cp build/release/minecraft-one-week-challenge minecraft-one-week-challenge/minecraft-one-week-challenge
else
    target_debug
fi

cp -R assets minecraft-one-week-challenge/

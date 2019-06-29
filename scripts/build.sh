#!/bin/bash

mkdir -p bin
cd bin 
mkdir -p release
mkdir -p debug

if [ "$1" = "release" ]
then
    cd release
    cmake -DCMAKE_BUILD_TYPE=Release ../..
    make
    echo "Built target in bin/release/"
else
    cd debug 
    cmake -DCMAKE_BUILD_TYPE=Debug ../..
    make
    echo "\nBuilt target in bin/debug/"
    echo "Use argument \"release\" to build in release mode."
fi

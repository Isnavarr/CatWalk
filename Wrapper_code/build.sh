#!/bin/bash

# TODO Add linker dependencies and other compile flags

#g++ PinTracerWrapper.cpp -o wrapper -fno-split-stack
g++ -L /home/jessicalam/Desktop/CatWalk/Toy2/ -Wall MyWrapper.cpp -o wrapper -lshared


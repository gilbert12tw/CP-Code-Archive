#!/bin/bash

echo "Hi"

echo "Compiling $1"

g++ -O2 $1

echo "Finish"

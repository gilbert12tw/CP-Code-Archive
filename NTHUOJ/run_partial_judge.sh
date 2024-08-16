#!/bin/zsh
cp $1.h function.h
gcc $1.c && ./a.out

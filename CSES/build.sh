#!/bin/bash
g++ -std=c++17 $1 -Wall -Wextra -Wshadow -fsanitize=address -g

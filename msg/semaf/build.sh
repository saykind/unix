#!/bin/bash

green='\e[0;32m'
NC='\e[0m'

gcc server.c -o Server.out
gcc plus.c -o Plus.out
gcc minus.c -o Minus.out
gcc end.c -o End.out
echo -e "Run ${green}Server.out${NC} in one terminal\n\
then you can run ${green}Plus.out${NC} and ${green}Minus.out${NC} which make opearations V(S) and P(S).\n\
Run ${green}End.out${NC} to shut server down correctly."

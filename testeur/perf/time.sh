#!/usr/bin/env bash

make re

printf "\n**** FT ****\n"
time ./ft_container 123
printf "\n**** STD ****\n"
time ./std_container 123

make fclean

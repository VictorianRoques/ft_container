#!/usr/bin/env bash

make re

printf "\n**** FT ****\n"
time ./ft_container
printf "\n**** STD ****\n"
time ./std_container

make fclean

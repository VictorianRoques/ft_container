#!/usr/bin/env bash

mkdir -p logs

clang++ -Wall -Werror -Wextra -std=c++98 -DTESTED_NAMESPACE=ft main.cpp
./a.out > logs/ft
clang++ -Wall -Werror -Wextra -std=c++98 -DTESTED_NAMESPACE=std main.cpp
./a.out > logs/std


printf "\nCheck diff between ft & std\n";
printf "****************************\n\n";
if diff logs/ft logs/std > deepthrougth;then
   printf "No diff between ft & std :)\n";
else
    printf "Diff between ft & std :(\n"
fi

rm ./a.out
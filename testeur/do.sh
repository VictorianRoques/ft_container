#!/usr/bin/env bash

make re
mkdir logs

./ft_container $1 $2 > logs/ft
./std_container $1 $2 > logs/std

cd logs

printf "\nCheck diff between ft & std\n";
printf "****************************\n\n";
if diff ft std > /dev/null;then
   printf "No diff between ft & std :)\n";
else
    printf diff ft std;
fi

cd ..
make fclean

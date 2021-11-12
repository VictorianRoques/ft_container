#!/usr/bin/env bash

cd ..  && make re
./ft_container > ft
./std_container > std

printf "\nCheck diff between ft & std\n";
printf "****************************\n\n";
if diff ft std > /dev/null;then
   printf "No diff between ft & std :)\n";
else
    printf diff ft std;
fi
make fclean

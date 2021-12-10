NAME 		=	ft_container
STD_NAME	=	std_container
CC			=	clang++
CFLAGS		=	-Wall -Werror -Wextra -std=c++98
OBJ 		=	$(SRC:.cpp=.o)
OBJ_STD		= 	$(SRC_STD:.cpp=.o)
SRC 		=	main.cpp
SRC_STD		=	main_std.cpp
RED			=	\033[0;31m
GREEN		=	\033[0;32m
WHITE		=	\033[0m

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_STD)
	@($(CC) $(CFLAGS) -o $(NAME)  $(OBJ))
	@($(CC) $(CFLAGS) -o $(STD_NAME) $(OBJ_STD))

clean:
	@rm -f $(OBJ) $(OBJ_STD)

fclean: clean
	@rm -f $(NAME) $(STD_NAME)

re: fclean all

.PHONY: all clean fclean re

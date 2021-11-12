NAME 		=	ft_container
STD_NAME	=	std_container
CC			=	clang++
CFLAGS		=	-Wall -Werror -Wextra -std=c++98
OBJ 		=	$(SRC:.cpp=.o)
SRC 		=	testeur/main.cpp

RED			=	\033[0;31m
GREEN		=	\033[0;32m
WHITE		=	\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@($(CC) $(CFLAGS) -o $(NAME) -DTESTED_NAMESPACE=ft $(OBJ))
	@($(CC) $(CFLAGS) -o $(STD_NAME) -DTESTED_NAMESPACE=std $(OBJ))

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME) $(STD_NAME)

re: fclean all

.PHONY: all clean fclean re

NAME 		=	ft_container
CC			=	clang++
CFLAGS		=	-Wall -Werror -Wextra -std=c++98
OBJ 		=	$(SRC:.cpp=.o)
SRC 		=	main.cpp

RED			=	\033[0;31m
GREEN		=	\033[0;32m
WHITE		=	\033[0m

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@printf "[ $(NAME) ] Compiling...\r"
	@($(CC) -o $(NAME) $(SRC) $(CFLAGS))

clean:
	@rm -f $(OBJ)
	@printf "Object files ${RED}removed\n${WHITE}"

fclean: clean
	@rm -f $(NAME)
	@printf "[ $(NAME) ] ${RED}removed\n${WHITE}"

re: fclean all

.PHONY: all clean fclean re
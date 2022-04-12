SRC		=	main.cpp test/utils_test.cpp test/vector_test.cpp\
			test/stack_test.cpp test/pair_test.cpp test/map_test.cpp test/set_test.cpp
OBJ		=	$(SRC:.cpp=.o)
NAME	=	ft_containers
CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -MD -MP -std=c++98
DEPENDS :=	$(SRC:.cpp=.d)


.PHONY	:	all re clean fclean

all		:	$(NAME)

$(NAME)	:	$(OBJ) Makefile
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o		:	%.cpp
			$(CC) $(CFLAGS) -c $< -o ${<:.cpp=.o}

clean	:	
			rm -f $(OBJ) $(DEPENDS)

fclean	:	clean
			rm -f $(NAME)

x		:	all
			./$(NAME)

leaks	:	all
			leaks --atExit -- ./$(NAME)

re		:	fclean all

-include $(DEPENDS)
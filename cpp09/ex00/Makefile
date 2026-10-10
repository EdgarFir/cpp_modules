NAME = ex00

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

CC = c++

FLAGS = -g -Wall -Werror -Wextra -pedantic

RM = rm -rf

all: $(NAME)

.cpp.o:
	$(CC) $(FLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGs) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 

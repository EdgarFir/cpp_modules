NAME = Base

SRCS = main.cpp Base.cpp

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -Wall -Werror -Wextra -std=c++98

CC = c++

RM = rm -rf

all: $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

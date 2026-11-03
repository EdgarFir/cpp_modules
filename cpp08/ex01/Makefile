NAME = ex00

SRCS = main.cpp Span.cpp

OBJS = $(SRCS:.cpp=.o)

CC= c++

CPPFLAGS = std=c++98 -Wall -Werror -Wextra -pedantic

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

run:
	./$(NAME)

.PHONY: all clean fclean re

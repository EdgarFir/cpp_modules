NAME = ex01

SRCS = $(addprefix src/, main.cpp Serializer.cpp)

OBJS = $(SRCS:.cpp=.o)

CC = c++

CPPFLAGS = -Wall -Wextra -Werror

STD = -std=c++98

all: $(NAME)

.cpp.o:
	$(CC) $(CPPFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

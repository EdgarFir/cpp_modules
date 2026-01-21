NAME = zombie

SRCS = main.cpp newZombie.cpp randomChump.cpp Zombie.cpp 

OBJS = $(SRCS:.cpp=.o)

CC = c++

CPPFLAGS = -Wall -Werror -Wextra -std=c++98

RM = rm -rf

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

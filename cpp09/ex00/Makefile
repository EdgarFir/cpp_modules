NAME = ex00

SRCS = main.cpp src/BitcoinExchange.cpp src/BitcoinExchangeFileReader.cpp src/BitcoinExchangeValidator.cpp

OBJS = $(SRCS:.cpp=.o)

CC= c++

CPPFLAGS = -std=c++98 -Wall -Werror -Wextra -pedantic

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

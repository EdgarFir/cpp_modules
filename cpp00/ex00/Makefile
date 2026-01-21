NAME = megaphone

SRCS = megaphone.cpp

OBJS = ${SRCS:.cpp=.o}

CC = c++

CFLAGS = -Wall -Werror -Wextra

STD98 = -std=c++98

RM = rm -rf

all: $(NAME)

.cpp.o:
	${CC} ${CFLAGS} ${STD98} -c $< -o ${<:.cpp=.o} 

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${STD98} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

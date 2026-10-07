NAME = fuzzer

SRC = 	./srcs/main.c \
		./srcs/init.c \
		./srcs/input_control.c \
		./srcs/process.c \
		./srcs/pipe.c \
		./srcs/free.c \
		./srcs/error.c \

VULN_SRC =  ./vuln_src/vuln1.c \
			./vuln_src/hang.c \

OBJ = ${SRC:.c=.o}

HEADER = fuzzer.h 

CC = cc 
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f
AR = ar rc
INCLUDES = -Iinclude

all:		${NAME}

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


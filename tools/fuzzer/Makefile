NAME = fuzzer

SRC = 	./srcs/main.c \
		./srcs/init.c \
		./srcs/input_control.c \
		./srcs/process.c \
		./srcs/pipe.c \
		./srcs/free.c \
		./srcs/error.c \

VULN_SRC1 =  ./vuln_src/vuln1.c 
VULN_SRC2 =	 ./vuln_src/hang.c 
VULN_SRC3 =	 ./vuln_src/vuln2.c
VULN_SRC4 =	 ./vuln_src/bof.c

EXEC_VULN = vuln1 \
			vuln2 \
			vuln3 \
			bof1

OBJ = ${SRC:.c=.o}

OBJ_VULN1 = ${VULN_SRC1:.c=.o}
OBJ_VULN2 = ${VULN_SRC2:.c=.o}
OBJ_VULN3 = ${VULN_SRC3:.c=.o}
OBJ_VULN4 = ${VULN_SRC4:.c=.o}

HEADER = fuzzer.h 

CC = cc 
CFLAGS = -Wall -Wextra -Werror -g3
VULN_CFLAGS = -Wall -Wextra -g3 -Iinclude -Wno-stringop-overflow
VULN_LDFLAGS = -fno-stack-protector -z execstack -no-pie
RM = rm -f
AR = ar rc
INCLUDES = -Iinclude

all:		${NAME}

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

vuln: 	$(EXEC_VULN)

vuln1: $(OBJ_VULN1)
	$(CC) $(CFLAGS) $(OBJ_VULN1) -o $@

vuln2: $(OBJ_VULN2)
	$(CC) $(CFLAGS) $(OBJ_VULN2) -o $@

vuln3: $(OBJ_VULN3)
	$(CC) $(CFLAGS) $(OBJ_VULN3) -o $@

bof1: $(OBJ_VULN4)
	$(CC) $(OBJ_VULN4) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@



clean:
	rm -f $(OBJ) $(OBJ_VULN1) $(OBJ_VULN2) $(OBJ_VULN3)

fclean: clean
	rm -f $(NAME) $(EXEC_VULN)

re: fclean all

.PHONY: all clean fclean re


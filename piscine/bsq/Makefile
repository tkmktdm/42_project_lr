NAME	= bsq

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= main.c \
		  read.c \
		  split.c \
		  parse.c \
		  solve.c \
		  output.c \
		  utils.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c bsq.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ft_putchar.c ft_swap.c ft_putstr.c ft_strlen.c ft_strcmp.c
SDIR	= ./srcs/
IDIR	= ./includes/
NAME	= libft.a
OBJS	= ${addprefix ${SDIR}, ${SRCS:.c=.o}}

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c -I ${IDIR} $< -o $@

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}
	ranlib ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re

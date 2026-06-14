NAME		= get_next_line.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -f

SRCS		= get_next_line.c get_next_line_utils.c
OBJS		= $(SRCS:.c=.o)
HEADERS		= get_next_line.h

ifdef BUFFER_SIZE
CFLAGS		+= -D BUFFER_SIZE=$(BUFFER_SIZE)
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

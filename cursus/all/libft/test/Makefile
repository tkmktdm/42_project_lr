NAME		= libft_test
LIBFT_DIR	= ..
LIBFT		= $(LIBFT_DIR)/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -I $(LIBFT_DIR)
RM			= rm -f

SRCS		= test_helpers.c test_main.c test_part1.c test_part2.c test_part3.c
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c test_helpers.h
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(NAME)

leaks: all
	leaks --atExit -- ./$(NAME)

valgrind: all
	valgrind --leak-check=full --error-exitcode=1 ./$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all run leaks valgrind clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/24 20:18:30 by tfujikaw          #+#    #+#              #
#    Updated: 2026/07/19 12:38:11 by htakumi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = push_swap

CC          = cc
CFLAG       = -Wall -Wextra -Werror
RM          = rm -f

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

HEADER      = push_swap.h

SRCS        = main.c simple_algorithm.c complex_algorithm.c \
              push_a_b.c swap_a_b.c \
              rotate_a_b.c rev_rotate_a_b.c \
              ft_disoder.c ft_strcmp.c stack_size.c ft_adaptive.c \
              args_parse.c check_duplicate.c stack_utils.c \
              chunk_utils.c medium_algorithm.c bench_print.c

OBJS        = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	 $(MAKE) -C $(LIBFT_DIR)
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAG) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAG) -I. -I$(LIBFT_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

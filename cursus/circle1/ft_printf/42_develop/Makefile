NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -f

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		=	ft_print_char.c \
				ft_printf.c \
				ft_print_hex.c \
				ft_print_int.c \
				ft_print_percent.c \
				ft_print_ptr.c \
				ft_print_str.c \
				ft_print_uint.c \
				ft_putnbr_base.c

OBJS		= $(SRCS:.c=.o)
DEPS		= $(SRCS:.c=.d)
HEADERS		= ft_printf.h

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) -MP -MMD $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re

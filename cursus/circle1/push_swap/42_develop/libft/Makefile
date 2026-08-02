# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/07 20:06:04 by tfujikaw          #+#    #+#              #
#    Updated: 2026/05/10 17:04:36 by tfujikaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CC		= cc
CFLAG	= -Wall -Wextra -Werror
LIB_CMD	= ar rc
RM		= rm -f

HEADER    = libft.h

SRCS_PART1    = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
              ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
              ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
              ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
              ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c

SRCS_PART2    = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
              ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRCS_PART3    = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
              ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRCS    = $(SRCS_PART1) $(SRCS_PART2) $(SRCS_PART3)

OBJS	= $(SRCS:.c=.o)

all: $(NAME)
# bonus: all

$(NAME): $(OBJS)
	$(LIB_CMD) $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAG) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

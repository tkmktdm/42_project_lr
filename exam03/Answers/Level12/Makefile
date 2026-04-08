CC      = cc
CFLAGS  = -Wall -Wextra -Werror

OBJS    = ft_list_remove_if.o sort_list.o
HEADERS = ft_list.h

all: $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean

re: fclean all

.PHONY: all clean fclean re

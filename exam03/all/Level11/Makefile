CC      = cc
CFLAGS  = -Wall -Wextra -Werror

OBJS    = ft_split.o

all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean

re: fclean all

.PHONY: all clean fclean re

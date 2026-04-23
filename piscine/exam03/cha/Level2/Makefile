CC      = cc
CFLAGS  = -Wall -Wextra -Werror

PROGS   =
OBJS    = ft_strcmp.o ft_strcpy.o ft_strrev.o

all: $(PROGS) $(OBJS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(PROGS)

re: fclean all

.PHONY: all clean fclean re

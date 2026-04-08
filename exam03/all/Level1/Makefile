CC      = cc
CFLAGS  = -Wall -Wextra -Werror

PROGS   = even odd interval_spaces rev_print
OBJS    = ft_putstr.o write_string.o

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

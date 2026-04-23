CC      = cc
CFLAGS  = -Wall -Wextra -Werror

PROGS   = aff_a
OBJS    = ft_ft.o

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

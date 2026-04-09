CC      = cc
CFLAGS  = -Wall -Wextra -Werror

PROGS   =
OBJS    = count_alen.o ft_strlen.o occ_a.o occ_z.o

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

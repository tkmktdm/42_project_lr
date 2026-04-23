CC      = cc
CFLAGS  = -Wall -Wextra -Werror

PROGS   = count_island

all: $(PROGS)

count_island: count_island.c count_island.h
	$(CC) $(CFLAGS) -o $@ count_island.c

clean:
	rm -f *.o

fclean: clean
	rm -f $(PROGS)

re: fclean all

.PHONY: all clean fclean re

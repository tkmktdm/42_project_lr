CC      = cc
CFLAGS  = -Wall -Wextra -Werror

PROGS   = inter is_palindrome last_word search_and_replace title union wdmatch

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o

fclean: clean
	rm -f $(PROGS)

re: fclean all

.PHONY: all clean fclean re

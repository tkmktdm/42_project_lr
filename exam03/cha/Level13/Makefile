CC      = cc
CFLAGS  = -Wall -Wextra -Werror

PROGS   = count_alpha

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o

fclean: clean
	rm -f $(PROGS)

re: fclean all

.PHONY: all clean fclean re

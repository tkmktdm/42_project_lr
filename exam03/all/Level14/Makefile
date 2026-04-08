CC      = cc
CFLAGS  = -Wall -Wextra -Werror

PROGS   = ord_alphlong str_maxlenoc

all: $(PROGS)

ord_alphlong: ord_alphlong.c ord_alphlong.h
	$(CC) $(CFLAGS) -o $@ ord_alphlong.c

str_maxlenoc: str_maxlenoc.c str_maxlenoc.h
	$(CC) $(CFLAGS) -o $@ str_maxlenoc.c

clean:
	rm -f *.o

fclean: clean
	rm -f $(PROGS)

re: fclean all

.PHONY: all clean fclean re

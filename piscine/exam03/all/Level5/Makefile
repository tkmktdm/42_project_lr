CC      = cc
CFLAGS  = -Wall -Wextra -Werror

PROGS   = alpha_mirror buzzfizz first_word fizzbuzz print_even \
          print_interval print_odd rot_13 rotone ulstr
OBJS    = swap_cases.o

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

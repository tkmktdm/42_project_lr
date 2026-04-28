SRCS_DIR	= ../htakumi
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I $(SRCS_DIR)
S			= $(SRCS_DIR)

# ===== Part 1: 複数ファイルが必要な関数 =====
test_strlcpy: test_strlcpy.c $(S)/ft_strlcpy.c $(S)/ft_strlen.c
	$(CC) $(CFLAGS) $^ -o $@

test_strlcat: test_strlcat.c $(S)/ft_strlcat.c $(S)/ft_strlen.c
	$(CC) $(CFLAGS) $^ -o $@

test_strnstr: test_strnstr.c $(S)/ft_strnstr.c $(S)/ft_strlen.c
	$(CC) $(CFLAGS) $^ -o $@

# ===== Part 2 =====
test_substr: test_substr.c $(S)/ft_substr.c $(S)/ft_strlen.c $(S)/ft_strdup.c
	$(CC) $(CFLAGS) $^ -o $@

test_strjoin: test_strjoin.c $(S)/ft_strjoin.c $(S)/ft_strlen.c
	$(CC) $(CFLAGS) $^ -o $@

test_strtrim: test_strtrim.c $(S)/ft_strtrim.c \
			  $(S)/ft_strlen.c $(S)/ft_strchr.c $(S)/ft_memcpy.c
	$(CC) $(CFLAGS) $^ -o $@

test_split: test_split.c $(S)/ft_split.c
	$(CC) $(CFLAGS) $^ -o $@

test_itoa: test_itoa.c $(S)/ft_itoa.c
	$(CC) $(CFLAGS) $^ -o $@

test_strmapi: test_strmapi.c $(S)/ft_strmapi.c $(S)/ft_strlen.c
	$(CC) $(CFLAGS) $^ -o $@

test_striteri: test_striteri.c $(S)/ft_striteri.c
	$(CC) $(CFLAGS) $^ -o $@

test_putchar_fd: test_putchar_fd.c $(S)/ft_putchar_fd.c
	$(CC) $(CFLAGS) $^ -o $@

test_putstr_fd: test_putstr_fd.c $(S)/ft_putstr_fd.c $(S)/ft_strlen.c
	$(CC) $(CFLAGS) $^ -o $@

test_putendl_fd: test_putendl_fd.c $(S)/ft_putendl_fd.c $(S)/ft_strlen.c
	$(CC) $(CFLAGS) $^ -o $@

test_putnbr_fd: test_putnbr_fd.c $(S)/ft_putnbr_fd.c
	$(CC) $(CFLAGS) $^ -o $@

# ===== Bonus =====
test_lstnew: test_lstnew.c $(S)/ft_lstnew.c
	$(CC) $(CFLAGS) $^ -o $@

test_lstsize: test_lstsize.c $(S)/ft_lstsize.c $(S)/ft_lstnew.c
	$(CC) $(CFLAGS) $^ -o $@

test_lstlast: test_lstlast.c $(S)/ft_lstlast.c $(S)/ft_lstnew.c
	$(CC) $(CFLAGS) $^ -o $@

test_lstadd_front: test_lstadd_front.c $(S)/ft_lstadd_front.c $(S)/ft_lstnew.c
	$(CC) $(CFLAGS) $^ -o $@

test_lstadd_back: test_lstadd_back.c \
				  $(S)/ft_lstadd_back.c $(S)/ft_lstlast.c $(S)/ft_lstnew.c
	$(CC) $(CFLAGS) $^ -o $@

test_lstdelone: test_lstdelone.c $(S)/ft_lstdelone.c $(S)/ft_lstnew.c
	$(CC) $(CFLAGS) $^ -o $@

test_lstclear: test_lstclear.c \
			   $(S)/ft_lstclear.c $(S)/ft_lstdelone.c $(S)/ft_lstnew.c
	$(CC) $(CFLAGS) $^ -o $@

test_lstiter: test_lstiter.c \
			  $(S)/ft_lstiter.c $(S)/ft_lstclear.c \
			  $(S)/ft_lstdelone.c $(S)/ft_lstnew.c
	$(CC) $(CFLAGS) $^ -o $@

test_lstmap: test_lstmap.c \
			 $(S)/ft_lstmap.c $(S)/ft_lstnew.c \
			 $(S)/ft_lstadd_back.c $(S)/ft_lstlast.c \
			 $(S)/ft_lstclear.c $(S)/ft_lstdelone.c
	$(CC) $(CFLAGS) $^ -o $@

# ===== Part 1: 単体でコンパイルできる関数 =====
test_%: test_%.c $(S)/ft_%.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: run_% clean
run_%: test_%
	./$<

clean:
	rm -f test_atoi test_bzero test_calloc test_isalnum test_isalpha \
		  test_isascii test_isdigit test_isprint test_memchr test_memcmp \
		  test_memcpy test_memmove test_memset test_strchr test_strdup \
		  test_strlcat test_strlcpy test_strlen test_strncmp test_strnstr \
		  test_strrchr test_tolower test_toupper \
		  test_substr test_strjoin test_strtrim test_split test_itoa \
		  test_strmapi test_striteri test_putchar_fd test_putstr_fd \
		  test_putendl_fd test_putnbr_fd \
		  test_lstnew test_lstsize test_lstlast test_lstadd_front \
		  test_lstadd_back test_lstdelone test_lstclear test_lstiter \
		  test_lstmap

SRCS_DIR = ../htakumi
CC 		 = cc
CFLAGS   = -Wall -Wextra -Werror

# テストしたい関数を追加していく
# test_strlen: test_strlen.c $(SRCS_DIR)/ft_strlen.c
# 	$(CC) $(CFLAGS) $^ -o $@ && ./$@

# test_atoi: test_atoi.c $(SRCS_DIR)/ft_atoi.c
# 	$(CC) $(CFLAGS) $^ -o $@ && ./$@

# テスト実行のコマンド作成
test_strlcpy: test_strlcpy.c $(SRCS_DIR)/ft_strlcpy.c $(SRCS_DIR)/ft_strlen.c
	$(CC) $(CFLAGS) $^ -o $@

test_strlcat: test_strlcat.c $(SRCS_DIR)/ft_strlcat.c $(SRCS_DIR)/ft_strlen.c
	$(CC) $(CFLAGS) $^ -o $@

test_strnstr: test_strnstr.c $(SRCS_DIR)/ft_strnstr.c $(SRCS_DIR)/ft_strlen.c
	$(CC) $(CFLAGS) $^ -o $@

test_%: test_%.c $(SRCS_DIR)/ft_%.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: run_%
.PHONY: test_%
run_%: test_%
	./$<

clean:
	rm -f test_*

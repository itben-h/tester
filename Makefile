NAME=hello
EXT=.out
MUNIT=munit.h munit.c
SRCS=$(shell find -name '*.c' ! -name "hello.c")
CC=cc
CFLAGS=-Wall -Wextra -Werror
RM=rm -rf
# VVV Directory Stuff VVV
LIBFT_PATH=../libft
LIB=-L$(LIBFT_PATH) -lft

lib:
	$(MAKE) -C $(LIBFT_PATH) all
	
lib-b:
	$(MAKE) -C $(LIBFT_PATH) bonus
	
test-lib: $(MUNIT) lib
	$(CC) $(CFLAGS) $(SRCS) $(LIB) -o $@$(EXT)
	
clean:
	$(RM) *$(EXT)
	
fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	
.PHONY.: all test clean lib lib-b

NAME=hello
EXT=.out
MUNIT=munit.h munit.c
SRC_LIB=test_libft.c
SRC_PNL=get_next_line.c get_next_line_utils.c
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
	
test-lib: $(MUNIT) lib-b
	$(CC) $(CFLAGS) $(SRC_LIB) $(LIB) -o $@$(EXT)

test-pnl: $(MUNIT)
	$(CC) $(CFLAGS) $(SRC_PNL)
	
clean:
	$(RM) *$(EXT)
	
fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	
.PHONY.: all test clean lib lib-b

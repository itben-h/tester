NAME=hello
EXT=.out
MUNIT=munit.h munit.c
SRCS=$(shell find -name '*.c' ! -name "hello.c")
CC=cc
CFLAGS=-Wall -Wextra -Werror
LIB=-L../ -lft
RM=rm -rf

all: $(NAME)

$(NAME): $(MUNIT)
	$(CC) $(CFLAGS) $(NAME).c munit.c -o $@$(EXT)

test:
	./$(NAME)$(EXT)

lib:
	$(MAKE) -C .. all
	
lib-b:
	$(MAKE) -C .. bonus
	
test-lib: $(MUNIT)
	$(CC) $(CFLAGS) $(SRCS) $(LIB) -o $@$(EXT)
	
clean:
	$(RM) *$(EXT)

.PHONY.: all test clean lib lib-b
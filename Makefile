NAME=hello
EXT=.out
MUNIT=munit.h munit.c

TEST_LIB=test_libft.c

SRC_GNL=$(addprefix $(PATH_GNL), \
	get_next_line.c \
	get_next_line_utils.c)
H_GNL=$(addprefix $(PATH_GNL), \
	get_next_line.h)
TEST_GNL=test_get_next_line.c
GNL_D=-D BUFFER_SIZE=42

CC=cc
CFLAGS=-Wall -Wextra -Werror
RM=rm -rf
MKDIR=mkdir -p

# VVV Directory Stuff VVV
DIR_BUILD=build/
INC=-I./$(DIR_BUILD)
SRC_BUILD=$(shell find $(DIR_BUILD) -name '*.c')
PATH_LIBFT=../libft/
PATH_GNL=../get_next_line/

LIB=-L$(PATH_LIBFT) -lft

lib:
	$(MAKE) -C $(PATH_LIBFT) all
	
lib-b:
	$(MAKE) -C $(PATH_LIBFT) bonus
	
test-lib: $(MUNIT) lib-b
	$(CC) $(CFLAGS) $(TEST_LIB) $(LIB) -o $@$(EXT)

test-gnl: $(MUNIT) $(DIR_BUILD)
	$(shell cp $(SRC_GNL) $(H_GNL) $(MUNIT) $(DIR_BUILD))
	$(CC) $(CFLAGS) $(SRC_BUILD) $(TEST_GNL) -g -o $@$(EXT)

$(DIR_BUILD): 
	$(MKDIR) $(DIR_BUILD)	

clean:
	@echo removing .out ...
	@$(RM) *$(EXT)

fclean: clean
	@echo removing build dir ...
	@$(RM) $(DIR_BUILD)

fclean-libft: clean
	$(MAKE) -C $(PATH_LIBFT) fclean
	
.PHONY.: all test clean fclean-libft compile

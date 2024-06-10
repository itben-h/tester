EXT=.out
MUNIT=munit.h munit.c
# --- Tests Files --- #

## ~~ libft ~~ ##
TEST_LIB=test_libft.c

## ~~ get_next_line ~~ ##
SRC_GNL=$(addprefix $(PATH_GNL), \
	get_next_line.c \
	get_next_line_utils.c)
SRC_GNL_B=$(addprefix $(PATH_GNL), \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c)
H_GNL=$(addprefix $(PATH_GNL), \
	get_next_line.h)
H_GNL_B=$(addprefix $(PATH_GNL), \
	get_next_line_bonus.h)
TEST_GNL=test_get_next_line.c
TEST_GNL_B=test_get_next_line_b.c

ifdef BUF
GNL_D=-D BUFFER_SIZE=$(BUF)
else
GNL_D=-D BUFFER_SIZE=1
endif

## ~~ ft_printf ~~ ##
TEST_PRINTF=test_printf.c

ifdef GG
TEST_PRINTF_B=test_printf-bb.c -w
else
TEST_PRINTF_B=$(CFLAGS) test_printf-b.c
endif

# --- Command Shortcuts --- #
CC=cc
CFLAGS=-Wall -Wextra -Werror
RM=rm -rf
MKDIR=mkdir -p
MAKE=make -C

# --- Directory Stuff --- #
DIR_BUILD=build/
INC=-I./$(DIR_BUILD)
SRC_BUILD=$(shell find $(DIR_BUILD) -name '*.c')
PATH_LIBFT=	../libft/
PATH_GNL=	../gnl/
PATH_PRINTF=	../printf/

LIB=		-L$(PATH_LIBFT) -lft
LIB_PRINTF=	-L$(PATH_PRINTF) -lftprintf

# --- RULES --- #
lib:
	$(MAKE) $(PATH_LIBFT) bonus

printf:
	$(MAKE) $(PATH_PRINTF) bonus

test-lib: $(MUNIT) lib
	$(CC) $(CFLAGS) munit.c $(TEST_LIB) $(LIB) -o $@$(EXT)

test-gnl: $(MUNIT) $(DIR_BUILD)
	$(shell cp $(SRC_GNL) $(H_GNL) $(MUNIT) $(DIR_BUILD))
	$(CC) $(CFLAGS) $(SRC_BUILD) $(TEST_GNL) $(GNL_D) -o $@$(EXT)
	
test-gnl-b: $(MUNIT) $(DIR_BUILD)
	$(shell cp $(SRC_GNL_B) $(H_GNL_B) $(MUNIT) $(DIR_BUILD))
	$(CC) $(CFLAGS) $(SRC_BUILD) $(TEST_GNL_B) $(GNL_D) -o $@$(EXT)

test-printf: $(MUNIT) printf
	$(CC) munit.c $(TEST_PRINTF) $(LIB_PRINTF) -g -o $@$(EXT)

test-printf-a: printf
	$(CC) test_printf_main.c $(LIB_PRINTF) -g -o $@$(EXT)
	
test-printf-b: $(MUNIT) printf
	$(CC) $(TEST_PRINTF_B) munit.c $(LIB_PRINTF) -g -o $@$(EXT)
	
$(DIR_BUILD): 
	$(MKDIR) $(DIR_BUILD)

clean:
	@echo removing .out ...
	@$(RM) *$(EXT)

fclean: clean
	@echo removing build dir ...
	@$(RM) $(DIR_BUILD)

fclean-libft: clean fclean
	$(MAKE) $(PATH_LIBFT) fclean

fclean-printf: clean fclean
	$(MAKE) $(PATH_PRINTF) fclean
	
.PHONY.: all test clean fclean-libft fclean-printf

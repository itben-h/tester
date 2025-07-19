########## Files & Dirs ##########
EXT			:= .test
BUILD_DIR	:= ./build/
SRC_DIR		:= ./src/
INC_DIR		:= ./inc/

UNITY_FILES	:=	$(addprefix $(SRC_DIR), \
				unity.c )

LIBFT		:= libft.a
LIBFT_LIB	:= -L$(BUILD_DIR) -lft
LIBFT_TESTS	:=	$(addprefix $(SRC_DIR), \
				unity_libft.c )

########## Compilation ##########
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
MAKE	:= make -C

UNITY_FLAGS	:= -DUNITY_INCLUDE_CONFIG_H

########## Custom ##########
MKDIR		:= mkdir -p
RM			:= rm -rf

COLOR_Y		:= \033[0;33m
COLOR_END	:= \033[0m

all:
	@echo "$(COLOR_Y)Specify which test you want to compile ...$(COLOR_END)"

make_build:
	@echo "$(COLOR_Y)building ...$(COLOR_END)"
	@$(MAKE) $(BUILD_DIR) all

$(LIBFT): make_build

libft: $(LIBFT) $(UNITY_FILES)
	@echo "$(COLOR_Y)compiling tests ...$(COLOR_END)"
	@$(CC) $(CFLAGS) $(UNITY_FILES) $(LIBFT_TESTS) -I$(INC_DIR) $(UNITY_FLAGS) $(LIBFT_LIB) -o $@$(EXT)

clean:
	@echo "$(COLOR_Y)removing build dir ...$(COLOR_END)"
	@$(RM) $(BUILD_DIR)

.PHONY.: all libft make_build

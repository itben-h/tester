NAME=libft.a

SRC=	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_lstcpy.c \
	ft_lstnew_dc.c \
	ft_lstadd_front_dc.c \
	ft_lstadd_back_dc.c \
	ft_lstclear_dc.c \
	get_next_line.c \

DIR_OBJ=obj/
OBJ=$(SRC:%.c=$(DIR_OBJ)%.o)
INC=-I./
CC=cc
CFLAG=-Wall -Wextra -Werror
AR=ar -rc
RM=rm -rf
MKDIR=mkdir -p

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(OBJ): | $(DIR_OBJ)

$(DIR_OBJ)%.o: %.c
	@$(CC) $(CFLAG) $(INC) -c -g $< -o $@

$(DIR_OBJ):
	$(MKDIR) $(DIR_OBJ)

clean:
	@echo removing objs ...
	@$(RM) $(DIR_OBJ)

fclean : clean
	@echo removing lib ...
	@$(RM) $(NAME)

re : fclean all

.PHONY.: all clean fclean re

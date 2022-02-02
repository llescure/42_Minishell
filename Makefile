
NAME = minishell

LIBFT		=	./srcs/libft/libft.a
LIBFT_DIR	=	./srcs/libft

OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lreadline

SRCS =	./srcs/main.c		\
		./srcs/exec/builtin.c	\
		./srcs/utils/utils.c		\
		./srcs/utils/ft_split_linked_list.c		\
		./srcs/exec/launch_shell.c		\
		./srcs/exec/signals.c		\
		./srcs/parsing/parsing.c		\
		./srcs/parsing/initialization.c		\
		./srcs/parsing/error_handling.c		\

BLACK		:= $(shell tput -Txterm setaf 0)
RED		:= $(shell tput -Txterm setaf 1)
GREEN		:= $(shell tput -Txterm setaf 2)
YELLOW		:= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
PURPLE		:= $(shell tput -Txterm setaf 5)
BLUE		:= $(shell tput -Txterm setaf 6)
WHITE		:= $(shell tput -Txterm setaf 7)
RESET		:= $(shell tput -Txterm sgr0)

SAN = -g3 -fsanitize=address
RM = rm -rf

$(NAME): $(OBJS)
		@echo "$(LIGHTPURPLE)Compilation...$(RESET)"
		$(MAKE) -C $(LIBFT_DIR)
		@echo "$(PURPLE)Libft compiled$(RESET)"
		@(gcc -o $(NAME) $(SRCS) srcs/libft/libft.a $(CFLAGS))
		@echo "$(GREEN)Compilation OK$(RESET)"

all: $(NAME)

clean:
	@ $(RM) $(OBJS)
	@echo "$(RED)Deleting objects...$(RESET)"

fclean: clean
	@ $(RM) $(OBJS)
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)Deleting executables...$(RESET)"

re: fclean all

san:
	@(gcc -o $(NAME) $(SRCS) srcs/libft/libft.a $(CFLAGS) $(SAN))

.PHONY: all clean fclean re

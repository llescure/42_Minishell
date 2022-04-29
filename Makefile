
NAME = minishell

LIBFT		=	./srcs/libft/libft.a
LIBFT_DIR	=	./srcs/libft

OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -lreadline

SRCS =	./srcs/main.c								\
		./srcs/exec/command/ft_echo.c				\
		./srcs/exec/command/ft_exit.c				\
		./srcs/exec/command/ft_unset.c				\
		./srcs/exec/command/ft_binary.c				\
		./srcs/exec/command/ft_export1.c			\
		./srcs/exec/command/ft_export2.c			\
		./srcs/exec/command/ft_cd.c					\
		./srcs/exec/command/ft_pwd.c				\
		./srcs/exec/command/ft_env.c				\
		./srcs/exec/command/ft_executable.c			\
		./srcs/exec/launch_shell.c					\
		./srcs/exec/signals.c						\
		./srcs/exec/pipe_management1.c				\
		./srcs/exec/pipe_management2.c				\
		./srcs/exec/execute_input.c					\
		./srcs/exec/redirections_management.c		\
		./srcs/exec/heredoc_management.c			\
		./srcs/parsing/scanner.c					\
		./srcs/parsing/tokenizer.c					\
		./srcs/parsing/parsing.c					\
		./srcs/parsing/utils_parsing1.c				\
		./srcs/parsing/utils_parsing2.c				\
		./srcs/parsing/utils_scanner.c				\
		./srcs/parsing/utils_tokenizer.c			\
		./srcs/parsing/initialization.c				\
		./srcs/parsing/error_handling.c				\
		./srcs/parsing/create_command.c				\
		./srcs/parsing/expand_management1.c			\
		./srcs/parsing/expand_management2.c			\
		./srcs/parsing/quote_management.c			\
		./srcs/parsing/use_env.c					\
		./srcs/parsing/command_management.c			\
		./srcs/parsing/pipe_management.c			\
		./srcs/parsing/redirection_management1.c	\
		./srcs/parsing/redirection_management2.c	\
		./srcs/parsing/increment_shlvl.c			\
		./srcs/parsing/utils_for_struct1.c			\
		./srcs/parsing/utils_for_struct2.c			\

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

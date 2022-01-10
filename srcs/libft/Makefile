# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llescure <llescure@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/26 17:55:58 by llescure          #+#    #+#              #
#    Updated: 2021/05/12 10:35:11 by llescure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = srcs/convert/ft_itoa.c \
	  	srcs/convert/ft_atoi.c \
	  	srcs/convert/ft_toupper.c \
	  	srcs/convert/ft_tolower.c \
		srcs/display/ft_putchar_fd.c \
  		srcs/display/ft_putstr_fd.c \
	  	srcs/display/ft_putendl_fd.c \
	  	srcs/display/ft_putnbr_fd.c \
		srcs/get_next_line/get_next_line.c \
		srcs/get_next_line/get_next_line_utils.c \
		srcs/memory/ft_memset.c \
  		srcs/memory/ft_bzero.c \
	  	srcs/memory/ft_memcpy.c \
	  	srcs/memory/ft_memccpy.c \
	  	srcs/memory/ft_memmove.c \
	  	srcs/memory/ft_memchr.c \
	  	srcs/memory/ft_memcmp.c \
	  	srcs/memory/ft_calloc.c \
	  	srcs/strings/ft_strlen.c \
	  	srcs/strings/ft_strchr.c \
	  	srcs/strings/ft_strrchr.c \
	  	srcs/strings/ft_strncmp.c \
	  	srcs/strings/ft_strlcpy.c \
	  	srcs/strings/ft_strlcat.c \
	  	srcs/strings/ft_strnstr.c \
	  	srcs/strings/ft_strdup.c \
	  	srcs/strings/ft_substr.c \
	  	srcs/strings/ft_strjoin.c \
	  	srcs/strings/ft_strtrim.c \
	  	srcs/strings/ft_split.c \
	  	srcs/strings/ft_strmapi.c \
	  	srcs/types/ft_isalpha.c \
	  	srcs/types/ft_isdigit.c \
	  	srcs/types/ft_isalnum.c \
	  	srcs/types/ft_isascii.c \
	  	srcs/types/ft_isprint.c \

BONUS = srcs/linked_lists/ft_lstnew.c \
		srcs/linked_lists/ft_lstsize.c \
		srcs/linked_lists/ft_lstlast.c \
		srcs/linked_lists/ft_lstadd_front.c \
		srcs/linked_lists/ft_lstdelone.c \
		srcs/linked_lists/ft_lstadd_back.c \
		srcs/linked_lists/ft_lstiter.c \
		srcs/linked_lists/ft_lstclear.c \
		srcs/linked_lists/ft_lstmap.c \
		srcs/double_linked_lists/ft_double_lstadd_back.c \
		srcs/double_linked_lists/ft_double_lstadd_front.c \
		srcs/double_linked_lists/ft_double_lstclear.c \
		srcs/double_linked_lists/ft_double_lstdelone.c \
		srcs/double_linked_lists/ft_double_lstfirst.c \
		srcs/double_linked_lists/ft_double_lstlast.c \
		srcs/double_linked_lists/ft_double_lstnew.c \
		srcs/double_linked_lists/ft_double_lstsize.c \
		srcs/double_linked_lists/ft_double_print_list.c \

HEADER = ../libft.h

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = /bin/rm -f

ifdef WITH_BONUS
ALL_OBJS = $(OBJS) $(BONUS_OBJS)
else
ALL_OBJS = $(OBJS)
endif

all:	 $(NAME)

$(NAME) : $(ALL_OBJS)
			ar rcs $(NAME) $(ALL_OBJS)

%.o : %.c $(HEADER)
			$(CC)  -c $(CFLAGS) $< -o $@

clean:
		$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

bonus : 
	$(MAKE) WITH_BONUS=1 all

.PHONY: all clean fclean re bonus

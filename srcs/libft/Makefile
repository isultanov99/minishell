# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/17 18:40:09 by cpablo            #+#    #+#              #
#    Updated: 2021/09/17 18:40:09 by cpablo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a

CFLAGS	= -Wall -Wextra -Werror

SRCS	= ft_memset.c \
	ft_bzero.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strchr.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isprint.c \
	ft_tolower.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strcmp.c \
	ft_split.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putnbr_fd.c \
	ft_itoa.c \
	ft_split_set.c \
	ft_free_array.c \
	ft_strlen_chr.c \
	ft_strnjoin.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_realloc_arr.c

OBJS	= $(SRCS:.c=.o)

INC		= libft.h

RM		= rm -f

all:	$(NAME)

$(NAME): $(OBJS)
		@ar rcs $(NAME) $?

%.o:	%.c
		@gcc $(CFLAGS) -c $^

clean:
		@$(RM) $(OBJS)

fclean:	clean
		@$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean

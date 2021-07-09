# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmangree <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 22:34:23 by bmangree          #+#    #+#              #
#    Updated: 2020/11/23 14:24:05 by bmangree         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCL =	libft.h
SRCS =	ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_split.c \
		ft_lstnew.c \
		ft_lstlast.c \
		ft_lstsize.c \
		ft_lstadd_front.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		get_next_line.c \
		get_next_line_utils.c

OBJ = $(SRCS:.c=.o)
FLAGS = -g -Wall -Wextra -Werror

$(NAME): 
		@gcc $(FLAGS) -c $(SRCS) $(INCL)
		@ar rcs $(NAME) $(OBJ)

all:	$(NAME)

clean:
		@rm -f $(OBJ) $(OBJB)

fclean:	clean
		@rm -f $(NAME)

re:		fclean $(NAME)

bonus:	all
		@gcc $(FLAGS) -c $(SRCB) -I $(INCL)
		@ar rcs $(NAME) $(OBJB)
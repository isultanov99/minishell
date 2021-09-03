# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/26 19:26:13 by natali            #+#    #+#              #
#    Updated: 2021/08/07 21:14:47 by lkarliah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= minishell

CFLAGS		= -lreadline -Wall -Wextra -Werror

LIBFT_FLAGS = -L./libft -lft

TERMCAP		= -ltermcap

SRCS_DIR	= srcs/

HEADER_DIR	= includes

SRC			= minishell_reverse.c \

SRCS 		= $(addprefix $(SRCS_DIR), $(SRC))

OBJS		= $(SRCS:.c=.o)

DEPENDS 	= $(SRCS:.c=.d)

INC			= includes/

LIB_DIR 	= libft/

RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C ./libft
			gcc $(CFLAGS) -I $(INC) $(LIBFT_FLAGS) $(TERMCAP) $^ -o $(NAME)

%.o:		%.c Makefile
			@gcc -I $(INC) -MMD -MP -c $< -o $@

bonus:		all

clean:
			@make clean -C ./libft
			@$(RM) $(OBJS) $(DEPENDS)

fclean:		clean
			@make fclean -C ./libft
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean

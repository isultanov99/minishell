# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 13:30:16 by cpablo            #+#    #+#              #
#    Updated: 2021/09/14 13:30:16 by cpablo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	= minishell

CFLAGS		= -lreadline -Wall -Wextra -Werror

LIBFT_FLAGS = -L./srcs/libft -lft

TERMCAP		= -ltermcap

SRCS_DIR	= srcs/

HEADER_DIR	= includes

SRC			= gnl/get_next_line_utils.c gnl/get_next_line.c gnl/gnl.c \
			main.c \
			minishell_reverse.c \
			bmangree/signal.c \
			cpablo/cd.c \
			cpablo/echo.c \
			cpablo/env.c \
			ft_exit.c \
			ft_input.c

SRCS 		= $(addprefix $(SRCS_DIR), $(SRC))

OBJS		= $(SRCS:.c=.o)

DEPENDS 	= $(SRCS:.c=.d)

INC			= includes/

LIB_DIR 	= libft/

RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C ./srcs/libft
			gcc $(CFLAGS) -I $(INC) $(LIBFT_FLAGS) $(TERMCAP) $^ -o $(NAME)

%.o:		%.c Makefile
			@gcc -I $(INC) -MMD -MP -c $< -o $@

bonus:		all

clean:
			@make clean -C ./srcs/libft
			@$(RM) $(OBJS) $(DEPENDS)

fclean:		clean
			@make fclean -C ./srcs/libft
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean

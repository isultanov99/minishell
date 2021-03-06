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

CFLAGS		= -Wall -Wextra -Werror

LIBFT_FLAGS = -L./srcs/libft -lft

TERMREAD	= -ltermcap -lreadline

SRCS_DIR	= srcs/

HEADER_DIR	= includes

SRC			= gnl/get_next_line_utils.c gnl/get_next_line.c gnl/gnl.c \
			cd.c \
			echo.c \
			env.c \
			ft_builtin.c \
			ft_cmd.c \
			ft_dlist.c \
			ft_dollar_quotes.c \
			ft_exit.c \
			ft_input.c \
			ft_key.c \
			ft_output.c \
			ft_parse_utils.c \
			ft_pipes.c \
			ft_redirects.c \
			ft_shlvl.c \
			ft_tc.c \
			ft_unset.c \
			aux_utils.c \
			aux_utils2.c \
			aux_utils3.c \
			aux_utils4.c \
			aux_utils5.c \
			aux_utils6.c \
			aux_utils7.c \
			aux_utils8.c \
			main.c \
			ft_cmd_utils.c \
			signal.c

SRCS 		= $(addprefix $(SRCS_DIR), $(SRC))

OBJS		= $(SRCS:.c=.o)

DEPENDS 	= $(SRCS:.c=.d)

INC			= includes/

LIB_DIR 	= libft/

RM			= rm -f

BOLD = \033[1m
COLOR_REGULAR = \033[0m
COLOR_GREEN = \033[32m

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C ./srcs/libft
			gcc $(CFLAGS) -I$(INC) $^ $(LIBFT_FLAGS) $(TERMREAD) -o $(NAME)
			@echo "$(BOLD)$(COLOR_GREEN)[OK]$(COLOR_REGULAR) Let's go crazy!"

%.o:		%.c Makefile
			@gcc -I $(INC) -MMD -MP -c $< -o $@

bonus:		all

clean:
			@make clean -C ./srcs/libft
			@$(RM) $(OBJS) $(DEPENDS)
			@echo "$(BOLD)$(COLOR_GREEN)[OK]$(COLOR_REGULAR) Files .o has been removed"

fclean:		clean
			@make fclean -C ./srcs/libft
			@$(RM) $(NAME)
			@echo "$(BOLD)$(COLOR_GREEN)[OK]$(COLOR_REGULAR) Our minishell has been removed"

re:			fclean all

.PHONY:		all clean fclean re

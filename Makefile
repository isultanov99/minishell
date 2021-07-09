NAME =		minishell

FLAGS =		-g3 -fsanitize=address -Wall -Wextra -Werror

SRC =		main.c

SRCS_DIR =	./srcs/

SRCS =		$(addprefix $(SRCS_DIR), $(SRC))

OBJS =		$(SRCS:c=o)

all:		$(NAME)

$(NAME):	$(OBJS) includes/minishell.h
			$(MAKE) -C libft
			gcc $(FLAGS) $(OBJS) -I./includes/ -L./libft/ -lft -lreadline -o minishell

clean:
			$(MAKE) clean -C ./libft
			rm -rf $(OBJS)

fclean:		clean
			rm -rf libft/libft.a
			rm -rf $(NAME)

re:			fclean all
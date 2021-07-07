NAME = minishell

SRC = main.c

SRCS_DIR = srcs/

SRCS = $(addprefix $(SRCS_DIR), $(SRC))

OBJS = $(SRCS:c=o)

all: $(NAME)

$(NAME): $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

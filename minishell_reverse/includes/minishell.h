#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <string.h>
# include "libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

typedef struct s_history
{
	int				hist_fd;
	t_dlist			*hist_start;
	t_dlist			*hist_end;
	int				flag;
	char			*hist_buf;
	char			*command;
	int				hist_print;
	int				command_print;
}					t_history;

/*
**	args содержит:
**	1. первым элементом название команды
**	2. опции
**	3. аргументы
**	4. последним элементом NULL
*/

typedef struct s_cmd
{
	char			**args;
	char			*path;
	int				input;
	int				output;
	int				file_error;
	int				stop;
	int				pipe_fd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}t_cmd;

/*
**	главная структура
*/

typedef struct s_data
{
	struct termios	termset;
	t_list			*env;
	t_history		history;
	int				status;
	int				sig_pid;
}					t_data;

t_data	g_main;

/*
**	env_exp
*/

void	env_get(char **envp);
void	env_free(t_list *list);
void	env_print(int fd);
void	env_add_new_var(char *var, char *value);
int		env_change_var(char *var, char *value);
char	*env_get_var(char *var);
int		env_delete_var(char *var);
t_list	*env_get_str(char *var, int var_size);
void	shlvl_set(void);
char	**envp_arr(void);
void	envp_arr_free(char **envp_arr);

/*
**	dlist
*/

t_dlist	*dlist_new(void *content);
void	dlist_add_back(t_dlist **dlist, t_dlist *new);
void	dlist_print(t_dlist *dlist);
void	dlist_free(t_dlist *dlist);
void	dlist_end(void);

/*
**	input, keys, hist
*/

void	print_message(void);
void	input(void);
char	*str_end(char *str);
int		keys(char *key);
void	hist_create(void);
void	hist_add_str(char *str);
void	str_to_exec(char *str);
void	set_sig(void);
void	control_characters(char *str);

/*
**	setup termcaps
*/

int		output_func(int c);
void	setup_term(void);
void	reset_term(void);

/*
**	buildins
*/

int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_export(t_cmd *cmd);
int		ft_unset(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);
void	export_print(int fd);
int		var_valid(char *var);
void	var_print_error(int fd, char *var);

/*
**	parser
*/
void	skip_spaces(char **line);
void	dollar(char **line, char **superline);
void	single_quotes(char **line, char **superline, t_cmd *cmd);
void	double_quotes(char **line, char **superline, t_cmd *cmd);
void	simple_chr(char **line, char **superline);
void	parse_chr(char **line, char **superline, t_cmd *cmd);
t_cmd	*parse_str(t_cmd *cmd, char **line);
void	end_of_args(char **line, char **superline, t_cmd *cmd, int code);
void	tolower_builtin(t_cmd *cmd);
void	parse_cmd(char *line);

/*
** redirects and pipes
*/
void	add_redirect(t_cmd *cmd, char **line);
int		double_left(char **line);
void	add_pipe(t_cmd *cmd, char **line);
void	link_pipes(t_cmd *start);
void	close_pipes(t_cmd *cmd);

/*
** signals
*/

void	main_input_re(void);
void	hist_input_re(void);

/*
** commands utils
*/
void	put_back_cmd(t_cmd **start, t_cmd *new);
t_cmd	*cmd_init(void);
int		check_cmd(t_cmd *start);
void	*get_path(t_cmd *start, char **envp);
void	exec_cmd(t_cmd *cmd);
void	free_cmd(t_cmd *cmd);

#endif

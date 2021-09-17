#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
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
}			t_cmd;

typedef struct s_main
{
	struct termios	termset;
	t_list			*env;
	t_history		history;
	int				status;
	int				sig_pid;
}					t_main;
t_main		g_main;

int		check_path(char **path, t_cmd *cmd);
int		check_file(t_cmd *cmd);
char	*export_var(char *str);
void	space_skipper(char **line);
void	env_get(char **envp);
void	list_free(t_list *list);
void	env_print(int fd);
void	env_add_new_var(char *var, char *value);
int		env_change_var(char *var, char *value);
char	*env_get_var(char *var);
int		env_delete_var(char *var);
t_list	*env_get_str(char *var, int var_size);
void	shlvl_set(void);
char	**envp_arr(void);
void	envp_arr_free(char **envp_arr);
t_dlist	*dlist_new(void *content);
void	dlist_add_back(t_dlist **dlist, t_dlist *new);
void	dlist_print(t_dlist *dlist);
void	dlist_free(t_dlist *dlist);
void	dlist_end(void);
int		n_is_print(char *str);
void	dol_sign_status(char **line, char **superline);
void	hist_or_command(char *buf);
char	*get_command(char *str, char *add);
void	print_message(void);
void	input(void);
char	*str_end(char *str);
int		keys(char *key);
void	keypressenter(void);
void	home_dir(char *message);
void	hist_create(void);
void	hist_add_str(char *str);
void	str_to_exec(char *str);
void	set_sig(void);
void	control_characters(char *str);
int		output_func(int c);
void	setup_term(void);
void	reset_term(void);
int		choose_builtin(t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_export(t_cmd *cmd);
int		ft_unset(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
int		ft_exit(t_cmd *cmd);
t_cmd	*last_cmd(t_cmd *lst);
void	export_print(int fd);
void	fork_cmd_routine(t_cmd *cmd);
int		export_add(int fd, char *str);
int		var_valid(char *var);
void	var_print_error(int fd, char *var);
void	skip_spaces(char **line);
void	dol_sign(char **line, char **superline);
void	squotes(char **line, char **superline, t_cmd *cmd);
void	dquotes(char **line, char **superline, t_cmd *cmd);
void	simple_chr(char **line, char **superline);
void	parse_chr(char **line, char **superline, t_cmd *cmd);
t_cmd	*parse_str(t_cmd *cmd, char **line);
void	end_of_args(char **line, char **superline, t_cmd *cmd, int code);
void	tolower_builtin(t_cmd *cmd);
void	parse_cmd(char *line);
void	add_redirect(t_cmd *cmd, char **line);
int		get_input(char *stop, int heredoc_fd);
void	add_pipe(t_cmd *cmd, char **line);
void	link_pipes(t_cmd *start);
void	close_pipes(t_cmd *cmd);
void	hist_input(void);
void	main_input(void);
void	main_inp(void);
void	hist_inp(void);
void	sigquit_handler(int code);
void	sigint_handler(int code);
void	put_back_cmd(t_cmd **start, t_cmd *new);
t_cmd	*cmd_init(void);
int		check_cmd(t_cmd *start);
void	*get_path(t_cmd *start, char **envp);
void	exec_cmd(t_cmd *cmd);
void	free_cmd(t_cmd *cmd);

#endif

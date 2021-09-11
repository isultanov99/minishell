#include "../includes/minishell.h"

/*
builtins/cd.c
*/
void	cd_print_error(char *path, int fd)
{
	write(fd, "cd: ", 4);
	ft_putstr_fd(path, fd);
	write(fd, ": ", 2);
	ft_putstr_fd(strerror(errno), fd);
	write(fd, "\n", 1);
}

/* 
 * ПРОВЕРИТЬ НА УТЕЧКИ
*/

int	no_arg(int fd, char *pwd_path)
{
	char	*home_path;

	home_path = getenv("HOME");
	if (home_path == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", fd);
		return (1);
	}
	if (chdir(home_path) == 0)
	{
		env_change_var("OLDPWD", pwd_path);
		env_change_var("PWD", home_path);
		// free(home_path);
	}
	else
	{
		cd_print_error(home_path, fd);
		// free(home_path);
		return (1);
	}
	return (0);
}

int	with_arg(int fd, char *path, char *cwd_path, char *pwd_path)
{
	if (strcmp("/", cwd_path) == 0)
		return (0);
	if (chdir(path) == 0)
	{
		cwd_path = getcwd(NULL, 0);
		env_change_var("OLDPWD", pwd_path);
		env_change_var("PWD", cwd_path);
	}
	else
	{
		cd_print_error(path, fd);
		return (1);
	}
	return (0);
}

/*
**	path - папка назначения
*/
/* 
 * ПРОВЕРИТЬ НА УТЕЧКИ
*/

int	ft_cd(t_cmd *cmd)
{
	int		fd;
	char	*path;
	char	*cwd_path;
	char	*pwd_path;
	int		result;

	fd = cmd->output;
	path = cmd->args[1];
	cwd_path = getcwd(NULL, 0);
	pwd_path = getenv("PWD");
	if (!path)
		result = no_arg(fd, pwd_path);
	else
		result = with_arg(fd, path, cwd_path, pwd_path);
	free(cwd_path);
	// free(pwd_path);
	return (result);
}

/*
builtins/ft_echo.c
*/
/*
**	проверяет, является ли строка опцией
**	возвращает 0, если это опция, иначе - 1
*/

int	echo_aux(char *str)
{
	int		i;

	i = 0;
	if (str[i] != '-')
		return (1);
	i = 1;
	if (str[i] != 'n')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	check_params(char *param, int fd)
{
	if (param == NULL)
	{
		write(fd, "\n", 1);
		return (1);
	}
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
	int		fd;
	char	**params;
	int		i;
	int		option;

	fd = cmd->output;
	params = cmd->args;
	i = 1;
	if (check_params(params[i], fd) == 1)
		return (0);
	option = 0;
	if (echo_aux(params[i]) == 0)
		option = 1;
	while (params[i] && echo_aux(params[i]) == 0)
		i++;
	while (params[i])
	{
		ft_putstr_fd(params[i], fd);
		if (params[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (option == 0)
		write(fd, "\n", 1);
	return (0);
}

/*
builtins/env.c
*/
int	ft_env(t_cmd *cmd)
{
	int	fd;

	fd = cmd->output;
	env_print(fd);
	return (0);
}

/*
builtins/ft_exit.c
*/
int	exit_code_valid(char *code)
{
	int		i;

	i = 0;
	if (code[i] == '-' || code[i] == '+')
		i = 1;
	while (code[i])
	{
		if (ft_isdigit(code[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(t_cmd *cmd)
{
	int		fd;
	char	**params;
	int		exit_code;

	fd = cmd->output;
	params = cmd->args;
	if (params[1] == NULL)
		ft_putstr_fd("exit\n", fd);
	if (params[1] == NULL)
		exit(0);
	if (params[2])
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", fd);
		return (1);
	}
	if (exit_code_valid(params[1]))
	{
		ft_putstr_fd("exit\nexit: ", fd);
		ft_putstr_fd(params[1], fd);
		ft_putstr_fd(": numeric argument required\n", fd);
		exit(255);
	}
	exit_code = ft_atoi(params[1]);
	ft_putstr_fd("exit\n", fd);
	exit(exit_code);
}

/*
builtins/ft_export_print.c
*/
/*
**	сортирует переменные экспорта в
**	алфавитном порядке по возрастанию
*/

void	exp_sort(t_list *list)
{
	t_list	*i;
	t_list	*j;
	char	*buf;

	i = list;
	while (i)
	{
		j = list;
		while (j)
		{
			if (strcmp(i->content, j->content) < 0)
			{
				buf = i->content;
				i->content = j->content;
				j->content = buf;
			}
			j = j->next;
		}
		i = i->next;
	}
}

/*
**	создаёт односвязный список - дубликат,
**	состоящий из переменных окружения
*/

t_list	*env_dup(void)
{
	t_list	*begin_env;
	t_list	*dup_env;

	begin_env = g_data.env;
	dup_env = NULL;
	while (begin_env)
	{
		ft_lstadd_back(&dup_env, ft_lstnew(ft_strdup(begin_env->content)));
		begin_env = begin_env->next;
	}
	return (dup_env);
}

void	str_put(char *s, int fd)
{
	int		i;
	int		flag;

	if (s == NULL)
		return ;
	i = 0;
	flag = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		if (s[i] == '=' && flag == 0)
		{
			write(fd, "\"", 1);
			flag = 1;
		}
		i++;
	}
	if (flag == 1)
		write(fd, "\"", 1);
}

/*
**	выводит переменные окружения через export без аргументов
*/

void	export_print(int fd)
{
	t_list	*list;
	t_list	*mind;

	list = env_dup();
	mind = list;
	exp_sort(list);
	while (list)
	{
		ft_putstr_fd("declare -x ", fd);
		str_put((char *)list->content, fd);
		write(fd, "\n", 1);
		list = list->next;
	}
	env_free(mind);
}

/*
builtins/ft_export.c
*/
char	*export_var(char *str)
{
	char	*var;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

void	export_value_mem_fill(char *value, char *str, int i)
{
	int		k;

	k = 0;
	while (str[i])
	{
		value[k] = str[i];
		k++;
		i++;
	}
	value[k] = '\0';
}

char	*export_value(char *str)
{
	char	*value;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	j = i;
	k = 0;
	while (str[i])
	{
		i++;
		k++;
	}
	value = (char *)malloc(sizeof(char) * (k + 1));
	i = j;
	export_value_mem_fill(value, str, i);
	return (value);
}

int	export_add(int fd, char *str)
{
	char	*var;
	char	*value;
	int		is_changed;

	var = export_var(str);
	if (var_valid(var) == 1)
	{
		var_print_error(fd, var);
		free(var);
		return (1);
	}
	value = export_value(str);
	is_changed = env_change_var(var, value);
	if (is_changed)
		env_add_new_var(var, value);
	free(var);
	free(value);
	return (0);
}

int	ft_export(t_cmd *cmd)
{
	int		fd;
	char	**params;
	int		i;

	fd = cmd->output;
	params = cmd->args;
	i = 1;
	if (params[i] == NULL)
	{
		export_print(fd);
		return (0);
	}
	while (params[i])
	{
		if (export_add(fd, params[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

/*
builtins/ft_pwd.c
*/
int	ft_pwd(t_cmd *cmd)
{
	int		fd;
	char	**params;
	char	*pwd_path;

	fd = cmd->output;
	params = cmd->args;
	pwd_path = getcwd(NULL, 0);
	if (pwd_path == NULL)
		return (1);
	ft_putstr_fd(pwd_path, fd);
	write(fd, "\n", 1);
	free(pwd_path);
	return (0);
}

/*
builtins/ft_unset.c
*/
/*
**	выводит сообщение об ошибке для export или unset
*/

void	var_print_error(int fd, char *var)
{
	write(fd, "export: `", 9);
	ft_putstr_fd(var, fd);
	write(fd, "': not a valid identifier\n", 26);
}

/*
**	проверяет на валидность переменную для export или unset
*/

int	var_valid(char *var)
{
	int		i;

	i = 0;
	if (ft_isalpha(var[i]) == 0)
		return (1);
	i = 1;
	while (var[i])
	{
		if (ft_isalnum(var[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(t_cmd *cmd)
{
	int		fd;
	char	**params;
	int		i;

	fd = cmd->output;
	params = cmd->args;
	i = 1;
	while (params[i])
	{
		if (var_valid(params[i]) == 1)
		{
			var_print_error(fd, params[i]);
			return (1);
		}
		env_delete_var(params[i]);
		i++;
	}
	return (0);
}

/*
builtins/shlvl.c
*/
/*
**	проверяет на валидность уровень
**	он должен быть только цифровой
**	succes = 0, fail = 1
*/

int	shlvl_valid(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}

/*
**	увеличивает на один уровень значение SHLVL
*/

void	shlvl_increment(char *shlvl)
{
	int		lvl;
	char	*new_shlvl;

	lvl = ft_atoi(shlvl);
	lvl += 1;
	new_shlvl = ft_itoa(lvl);
	env_change_var("SHLVL", new_shlvl);
	free(new_shlvl);
}

void	shlvl_set(void)
{
	char	*shlvl;
	int		is_changed;

	shlvl = env_get_var("SHLVL");
	if (shlvl == NULL)
	{
		is_changed = env_change_var("SHLVL", "1");
		if (is_changed == 1)
			env_add_new_var("SHLVL", "1");
		return ;
	}
	if (shlvl_valid(shlvl) == 1)
		env_change_var("SHLVL", "1");
	else
		shlvl_increment(shlvl);
	free(shlvl);
}


/*
cmd/cmd_utils.c
*/
int	ft_cmdlen(t_cmd *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_cmd	*last_cmd(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	put_back_cmd(t_cmd **start, t_cmd *new)
{
	t_cmd	*last;

	if (!*start)
	{
		*start = new;
		return ;
	}
	last = last_cmd(*start);
	last->next = new;
	new->prev = last;
}

int	check_cmd(t_cmd *start)
{
	while (start)
	{
		if (start->stop == 1)
			return (1);
		start = start->next;
	}
	return (0);
}

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->input = STDIN_FILENO;
	cmd->output = STDOUT_FILENO;
	cmd->stop = 0;
	cmd->file_error = 0;
	return (cmd);
}

/*
cmd/exec_cmd.c
*/
int	choose_builin(t_cmd *cmd)
{
	if (!cmd->args)
		return (0);
	if (cmd->file_error)
		return (1);
	if (ft_strcmp("echo", cmd->args[0]) == 0)
		g_data.status = ft_echo(cmd);
	else if (ft_strcmp("cd", cmd->args[0]) == 0)
		g_data.status = ft_cd(cmd);
	else if (ft_strcmp("pwd", cmd->args[0]) == 0)
		g_data.status = ft_pwd(cmd);
	else if (ft_strcmp("export", cmd->args[0]) == 0)
		g_data.status = ft_export(cmd);
	else if (ft_strcmp("unset", cmd->args[0]) == 0)
		g_data.status = ft_unset(cmd);
	else if (ft_strcmp("env", cmd->args[0]) == 0)
		g_data.status = ft_env(cmd);
	else if (ft_strcmp("exit", cmd->args[0]) == 0)
		g_data.status = ft_exit(cmd);
	else
		return (0);
	return (1);
}

void	fork_cmd_routine(t_cmd *cmd)
{
	char	**tmp;

	tmp = envp_arr();
	dup2(cmd->input, STDIN_FILENO);
	dup2(cmd->output, STDOUT_FILENO);
	close_pipes(cmd);
	if (!(get_path(cmd, tmp)))
		exit(g_data.status);
	if (cmd->file_error)
		exit(g_data.status);
	g_data.status = execve(cmd->path, cmd->args, tmp);
	ft_free_array((void **)tmp);
	if (g_data.status < 0)
	{
		if (errno == ENOEXEC)
			exit(EXIT_SUCCESS);
		else if (errno == EACCES)
		{
			perror(cmd->args[0]);
			exit(126);
		}
		else
			perror(cmd->args[0]);
	}
	exit (g_data.status);
}

void	single_cmd(t_cmd *cmd)
{
	int		status;

	if (!choose_builin(cmd))
	{
		g_data.sig_pid = fork();
		if (g_data.sig_pid == 0)
			fork_cmd_routine(cmd);
		else if (g_data.sig_pid < 0)
			exit(EXIT_FAILURE);
		wait(&status);
		if (g_data.status != 130 && g_data.status != 131)
			g_data.status = WEXITSTATUS(status);
		g_data.sig_pid = 0;
	}
}

void	multi_cmd(t_cmd *cmd)
{
	int		status;

	while (cmd)
	{
		g_data.sig_pid = fork();
		if (g_data.sig_pid == 0)
		{
			if (!choose_builin(cmd))
				fork_cmd_routine(cmd);
			else
				exit(g_data.status);
		}
		else if (g_data.sig_pid < 0)
			exit(EXIT_FAILURE);
		if (!cmd->next)
			close_pipes(cmd);
		cmd = cmd->next;
	}
	while (wait(&status) != -1 && errno != ECHILD)
		g_data.status = WEXITSTATUS(status);
	g_data.sig_pid = 0;
}

void	exec_cmd(t_cmd *cmd)
{
	if (cmd->args)
	{
		reset_term();
		if (!cmd->next)
			single_cmd(cmd);
		else
			multi_cmd(cmd);
		setup_term();
	}
	free_cmd(cmd);
}

/*
cmd/path_utils.c
*/
void	*path_name(char *path, char *cmd_name, t_cmd *cmd)
{
	struct stat	buff;
	char		*new;
	int			fd;

	new = ft_strdup(path);
	new = ft_strnjoin(new, "/", 1);
	new = ft_strnjoin(new, cmd_name, ft_strlen(cmd_name));
	if ((stat(new, &buff)) == 0)
	{
		cmd->path = ft_strdup(new);
		free (new);
		return ((void *)1);
	}
	free (new);
	return (NULL);
}

int	check_path(char **path, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if ((path_name(path[i], cmd->args[0], cmd)))
			return (1);
		i++;
	}
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	g_data.status = 127;
	return (0);
}

int	check_file(t_cmd *cmd)
{
	struct stat	buff;

	if ((ft_strchr(cmd->args[0], '/')))
	{
		if ((stat(cmd->args[0], &buff)) < 0)
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_data.status = 127;
			return (-1);
		}
		else if (S_ISDIR(buff.st_mode))
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			g_data.status = 126;
			return (-1);
		}
		else
		{
			cmd->path = ft_strdup(cmd->args[0]);
			return (0);
		}
	}
	return (1);
}

void	*get_path(t_cmd *cmd, char **envp)
{
	char	**path;

	path = NULL;
	if (!cmd->args || !envp)
		return (NULL);
	while (*envp)
	{
		if (!ft_strncmp("PATH=", *envp, 5))
			path = ft_split(*envp + 5, ':');
		envp++;
	}
	if (!path)
	{
		ft_putstr_fd("Error: cannot find PATH variable\n", 2);
		g_data.status = 1;
		return (ft_free_array((void **)path));
	}
	if ((check_file(cmd)) == -1)
		return (ft_free_array((void **)path));
	else if ((check_file(cmd)) == 1)
		if (!check_path(path, cmd))
			return (ft_free_array((void **)path));
	ft_free_array((void **)path);
	return ((void *)1);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->path)
			free(cmd->path);
		if (cmd->args)
			ft_free_array((void **)cmd->args);
		free (cmd);
		cmd = tmp;
	}
}

/*
envp/env_1.c
*/
/*
**	создаёт односвязный список, состоящий
**	из переменных окружения
*/

void	env_get(char **envp)
{
	t_list	*list;
	int		i;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	g_data.env = list;
}

/*
**	полностью очищает память односвязного списка
*/

void	env_free(t_list *list)
{
	t_list	*mind;

	while (list)
	{
		mind = list->next;
		free(list->content);
		free(list);
		list = mind;
	}
}

/*
**	выводит переменные окружения
*/

void	env_print(int fd)
{
	t_list	*cp;

	cp = g_data.env;
	while (cp)
	{
		if (ft_strchr((char *)cp->content, '='))
		{
			ft_putstr_fd((char *)cp->content, fd);
			write(fd, "\n", 1);
		}
		cp = cp->next;
	}
}

/*
**	возвращает элемент односвязного списка, в котором
**	содержится строка, которая предшествует строке, в
**	которой содержится переменная, которую нужно удалить
*/

static t_list	*env_get_pre_str(char *var, int var_size)
{
	t_list	*cp;

	cp = g_data.env;
	if (cp && ft_strncmp((char *)cp->content, var, var_size) == 0
		&& (((char*)cp->content)[var_size] == '='
		|| ((char*)cp->content)[var_size] == '\0'))
		return (NULL);
	while (cp)
	{
		if (cp->next
			&& ft_strncmp((char *)(cp->next)->content, var, var_size) == 0
			&& (((char*)(cp->next)->content)[var_size] == '='
			|| ((char*)(cp->next)->content)[var_size] == '\0'))
			break ;
		cp = cp->next;
	}
	return (cp);
}

/*
**	удаляет из списка элемент, в котором
**	содержится переменная, поданная на вход
**	возвращает 0 в случае успеха и 1 в ином случае
*/

int	env_delete_var(char *var)
{
	int		var_size;
	t_list	*str;
	t_list	*pre;

	var_size = ft_strlen(var);
	str = env_get_str(var, var_size);
	if (str == NULL)
		return (1);
	pre = env_get_pre_str(var, var_size);
	if (pre == NULL)
		g_data.env = str->next;
	else
		pre->next = str->next;
	free(str->content);
	free(str);
	return (0);
}

/*
envp/env_2.c
*/
/*
**	создаёт строку из переменной и
**	её значения через знак равно
*/

static char	*env_new_str(char *var, char *value)
{
	char	*new_str;
	char	*mind;

	if (value == NULL)
		return (ft_strdup(var));
	new_str = ft_strjoin(var, "=");
	mind = new_str;
	new_str = ft_strjoin(new_str, value);
	free(mind);
	return (new_str);
}

/*
**	добавляет новую переменную
*/

void	env_add_new_var(char *var, char *value)
{
	char	*new_str;

	new_str = env_new_str(var, value);
	ft_lstadd_back(&(g_data.env), ft_lstnew(new_str));
}

/*
**	изменяет значение переменной, которую принимает
**	первым аргументом
**	возвращает 0 в случае успеха и 1 в ином случае
*/

int	env_change_var(char *var, char *value)
{
	int		var_size;
	t_list	*list;
	char	*new_str;

	var_size = ft_strlen(var);
	list = env_get_str(var, var_size);
	if (list == NULL)
		return (1);
	if (value == NULL)
		return (0);
	new_str = env_new_str(var, value);
	free(list->content);
	list->content = new_str;
	return (0);
}

/*
**	возвращает элемент односвязного списка, в котором
**	содержится строка с нужной переменной
**	если такой строки нет, то будет возвращено NULL
*/

t_list	*env_get_str(char *var, int var_size)
{
	t_list	*cp;

	cp = g_data.env;
	while (cp)
	{
		if (ft_strncmp((char *)cp->content, var, var_size) == 0
			&& (((char*)cp->content)[var_size] == '='
			|| ((char *)cp->content)[var_size] == '\0'))
			break ;
		cp = cp->next;
	}
	if (cp == NULL)
		return (NULL);
	return (cp);
}

/*
envp/env_3.c
*/
void	env_get_var_mem_fill(char *ret_str, char *var_str, int var_size)
{
	int		i;

	i = 0;
	while (var_str[var_size + 1] != '\0')
	{
		ret_str[i] = var_str[var_size + 1];
		var_size++;
		i++;
	}
	ret_str[i] = '\0';
}

/*
**	возвращает значение переменной, которую принимает
**	первым аргументом
*/

char	*env_get_var(char *var)
{
	int		var_size;
	t_list	*list;
	char	*var_str;
	int		i;
	char	*ret_str;

	var_size = ft_strlen(var);
	list = env_get_str(var, var_size);
	if (list == NULL)
		return (NULL);
	var_str = list->content;
	i = 0;
	while (var_str[var_size + 1] != '\0')
	{
		var_size++;
		i++;
	}
	ret_str = (char *)malloc(sizeof(char) * (i + 1));
	var_size = ft_strlen(var);
	env_get_var_mem_fill(ret_str, var_str, var_size);
	return (ret_str);
}

/*
**	создаёт отдельный двумерный массив из односвязного списка env
*/

char	**envp_arr(void)
{
	t_list	*envp_list;
	char	**envp_arr;
	int		i;

	envp_list = g_data.env;
	envp_arr = (char **)malloc(sizeof(char *) * (ft_lstsize(envp_list) + 1));
	i = 0;
	while (envp_list)
	{
		envp_arr[i] = ft_strdup(envp_list->content);
		i++;
		envp_list = envp_list->next;
	}
	envp_arr[i] = NULL;
	return (envp_arr);
}

void	envp_arr_free(char **envp_arr)
{
	int		i;

	i = 0;
	while (envp_arr[i])
	{
		free(envp_arr[i]);
		i++;
	}
	free(envp_arr);
}


/*
history/double_list.c
*/
t_dlist	*dlist_new(void *content)
{
	t_dlist	*new;

	new = (t_dlist *)malloc(sizeof(t_dlist));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	dlist_add_back(t_dlist **dlist, t_dlist *new)
{
	t_dlist	*begin;

	if (dlist == NULL || new == NULL)
		return ;
	if (*dlist == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*dlist = new;
		return ;
	}
	begin = *dlist;
	while (begin->next)
		begin = begin->next;
	begin->next = new;
	new->next = NULL;
	new->prev = begin;
}

void	dlist_print(t_dlist *dlist)
{
	t_dlist	*copy;

	copy = dlist;
	while (copy)
	{
		printf("%s", (char *)copy->content);
		copy = copy->next;
	}
}

void	dlist_free(t_dlist *dlist)
{
	t_dlist	*mind;

	while (dlist)
	{
		mind = dlist->next;
		free(dlist->content);
		free(dlist);
		dlist = mind;
	}
}

void	dlist_end(void)
{
	g_data.history.hist_end = g_data.history.hist_start;
	while (g_data.history.hist_end)
	{
		if (g_data.history.hist_end->next == NULL)
			break ;
		g_data.history.hist_end = g_data.history.hist_end->next;
	}
}

/*
history/hist.c
*/
void	hist_create(void)
{
	char	*path;
	char	*file_name;
	char	*str;

	path = env_get_var("HOME");
	file_name = ft_strjoin(path, "/.minishell_history");
	free(path);
	g_data.history.hist_fd
		= open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	close(g_data.history.hist_fd);
	g_data.history.hist_start = NULL;
	g_data.history.hist_fd = open(file_name, O_RDONLY);
	while (get_next_line(g_data.history.hist_fd, &str) > 0)
	{
		dlist_add_back(&(g_data.history.hist_start), dlist_new(ft_strdup(str)));
		free(str);
	}
	free(str);
	close(g_data.history.hist_fd);
	g_data.history.hist_fd
		= open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	free(file_name);
	dlist_end();
	g_data.history.flag = 0;
}

/*
**	добавляет введённую строку в историю
*/

void	hist_add_str(char *str)
{
	char	str_size;

	str_size = ft_strlen(str);
	write(g_data.history.hist_fd, str, str_size);
	write(g_data.history.hist_fd, "\n", 1);
	dlist_add_back(&(g_data.history.hist_start), dlist_new(ft_strdup(str)));
}

/*
parser/parse_builtins.c
*/
char	*str_tolower(char *str)
{
	char	*copy;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	i = -1;
	len = ft_strlen(str);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	ft_bzero((void *)copy, len + 1);
	while (++i < len)
		copy[i] = ft_tolower(str[i]);
	return (copy);
}

void	cmp_builtin(char *name)
{
	char	*tmp;

	if (!name)
		return ;
	tmp = str_tolower(name);
	if (!ft_strcmp(tmp, "cd") || !ft_strcmp(tmp, "echo")
		|| !ft_strcmp(tmp, "pwd") || !ft_strcmp(tmp, "env")
		|| !ft_strcmp(tmp, "exit") || !ft_strcmp(tmp, "export")
		|| !ft_strcmp(tmp, "unset"))
		ft_strlcpy(name, tmp, ft_strlen(name) + 1);
	free(tmp);
}

void	tolower_builtin(t_cmd *cmd)
{
	if (!cmd->args)
		return ;
	while (cmd && cmd->args)
	{
		cmp_builtin(cmd->args[0]);
		cmd = cmd->next;
	}
}

/*
parser/parse_dollar.c
*/
void	dollar_status(char **line, char **superline)
{
	char	*tmp_status;

	tmp_status = ft_itoa(g_data.status);
	*superline = ft_strnjoin(*superline, tmp_status, ft_strlen(tmp_status));
	free(tmp_status);
	(*line)++;
	g_data.status = 0;
}

void	dollar_get_value(char **line, char **superline, int len)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	key = ft_substr(*line, 0, len);
	value = env_get_var(key);
	if (value && *value)
		*superline = ft_strnjoin(*superline, value, ft_strlen(value));
	free(key);
	free(value);
	*line += len;
}

void	dollar(char **line, char **superline)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	(*line)++;
	if (**line == '?')
	{
		dollar_status(line, superline);
		return ;
	}
	else if (ft_isdigit(**line))
	{
		(*line)++;
		return ;
	}
	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '\''
		&& (*line)[i] != '\"')
		i++;
	if (!i)
	{
		*superline = ft_strnjoin(*superline, "$", 1);
		return ;
	}
	dollar_get_value(line, superline, i);
}

/*
parser/parse_utils.c
*/
void	skip_spaces(char **line)
{
	if (*line)
	{
		while (**line && **line == ' ')
			(*line)++;
	}
}

void	single_quotes(char **line, char **superline, t_cmd *cmd)
{
	*superline = ft_strnjoin(*superline, *line + 1,
			ft_strlen_chr(*line + 1, '\''));
	*line += ft_strlen_chr(*line + 1, '\'') + 2;
	if (cmd && !**line && !**superline)
		end_of_args(line, superline, cmd, 0);
}

void	double_quotes(char **line, char **superline, t_cmd *cmd)
{
	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '$')
			dollar(line, superline);
		else
		{
			*superline = ft_strnjoin(*superline, *line, 1);
			(*line)++;
		}
	}
	if (**line)
		(*line)++;
	if (cmd && !**superline && !**line)
		end_of_args(line, superline, cmd, 0);
}

void	simple_chr(char **line, char **superline)
{
	*superline = ft_strnjoin(*superline, *line, 1);
	(*line)++;
}

/*
parser/parser.c
*/
void	end_of_args(char **line, char **superline, t_cmd *cmd, int code)
{
	char	*tmp;

	if (!code)
		cmd->args = ft_realloc_arr(cmd->args, arr_len((void **)cmd->args),
				*superline);
	skip_spaces(line);
	if (!**line || code == 1)
	{
		free(*superline);
		*superline = NULL;
	}
	else
	{
		tmp = *superline;
		*superline = ft_strdup("\0");
		free (tmp);
		skip_spaces(line);
	}
}

void	parse_chr(char **line, char **superline, t_cmd *cmd)
{
	if (**line && **line == '\'')
		single_quotes(line, superline, cmd);
	else if (**line && **line == '\"')
		double_quotes(line, superline, cmd);
	else if (**line && **line == '$')
		dollar(line, superline);
	else if (**line && **line != '|' && **line != '<'
		&& **line != '>' && **line != ' ')
		simple_chr(line, superline);
}

int	parse_loop(t_cmd *cmd, char **line, char **superline)
{
	if (**line)
		parse_chr(line, superline, cmd);
	if (**line && (**line == '<' || **line == '>'))
	{
		add_redirect(cmd, line);
		if (!**line)
		{
			if (*superline)
				if (!**superline)
					end_of_args(line, superline, cmd, 1);
			end_of_args(line, superline, cmd, 0);
			return (1);
		}
	}
	if (**line && **line == '|')
	{
		add_pipe(cmd, line);
		if (*(*line - 1) != ' ')
			end_of_args(line, superline, cmd, 0);
		end_of_args(line, superline, cmd, 1);
		return (1);
	}
	if (**line && **line == ' ')
		end_of_args(line, superline, cmd, 0);
	return (0);
}

t_cmd	*parse_str(t_cmd *cmd, char **line)
{
	char		*superline;

	cmd = cmd_init();
	superline = ft_calloc(1);
	skip_spaces(line);
	while (**line)
		if ((parse_loop(cmd, line, &superline)))
			return (cmd);
	if (superline)
		if (!*superline)
			end_of_args(line, &superline, cmd, 1);
	end_of_args(line, &superline, cmd, 0);
	return (cmd);
}

void	parse_cmd(char *line)
{
	t_cmd		*start;
	t_cmd		*cmd;
	char		*superline;

	start = NULL;
	while (1)
	{
		cmd = parse_str(cmd, &line);
		put_back_cmd(&start, cmd);
		if (!*line)
			break ;
	}
	if (!(check_cmd(start)))
	{
		link_pipes(start);
		tolower_builtin(start);
		exec_cmd(start);
	}
	else
		free_cmd(start);
}



/*
pipes_and_redirects/add_pipe.c
*/
void	close_pipes(t_cmd *cmd)
{
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd->next)
	{
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
		cmd = cmd->next;
	}
}

void	link_pipes(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->next)
		{
			if (cmd->next->input == STDIN_FILENO)
				cmd->next->input = cmd->pipe_fd[0];
			if (cmd->output == STDOUT_FILENO)
				cmd->output = cmd->pipe_fd[1];
		}
		cmd = cmd->next;
	}
}

void	add_pipe(t_cmd *cmd, char **line)
{
	(*line)++;
	skip_spaces(line);
	if ((pipe(cmd->pipe_fd)) == -1)
	{
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}
}

/*
pipes_and_redirects/heredoc_redirect.c
*/
void	sigint_handler(int code)
{
	pid_t	id;

	(void)code;
	ft_putstr_fd("\n", 1);
	id = getpid();
	kill(id, SIGKILL);
}

void	sigquit_handler(int code)
{
	(void)code;
}

void	add_heredoc(char *end, int heredoc_fd)
{
	char	*input;

	input = "\0";
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			ft_putstr_fd("\b\b", 2);
			exit(0);
		}
		if (ft_strcmp(input, end))
		{
			ft_putstr_fd(input, heredoc_fd);
			ft_putstr_fd("\n", heredoc_fd);
		}
		else
			exit(0);
	}
}

int	get_input(char *stop, int heredoc_fd)
{
	int	status;

	reset_term();
	g_data.sig_pid = fork();
	if (g_data.sig_pid == 0)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, &sigquit_handler);
		add_heredoc(stop, heredoc_fd);
	}
	else if (g_data.sig_pid < 0)
		exit(EXIT_FAILURE);
	wait(&status);
	g_data.sig_pid = 0;
	close(heredoc_fd);
	status = WTERMSIG(status);
	return (status);
}

int	double_left(char **line)
{
	int		heredoc_fd;
	char	*stop;
	int		status;

	stop = ft_calloc(1);
	status = 0;
	*line = *line + 2;
	skip_spaces(line);
	while (**line && **line != ' ')
		parse_chr(line, &stop, NULL);
	heredoc_fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if ((get_input(stop, heredoc_fd)) > 0)
	{
		free(stop);
		setup_term();
		return (-1);
	}
	heredoc_fd = open(".heredoc", O_RDONLY);
	skip_spaces(line);
	free(stop);
	return (heredoc_fd);
}

/*
pipes_and_redirects/redirect.c
*/
int	double_right(char **line)
{
	char	*file;
	int		fd;

	file = ft_calloc(1);
	*line = *line + 2;
	skip_spaces(line);
	while (**line && **line != ' ')
		parse_chr(line, &file, NULL);
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		g_data.status = 1;
		perror(file);
	}
	skip_spaces(line);
	free(file);
	return (fd);
}

int	single_left(char **line)
{
	char	*file;
	int		fd;

	file = ft_calloc(1);
	(*line)++;
	skip_spaces(line);
	while (**line && **line != ' ')
		parse_chr(line, &file, NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		g_data.status = 1;
		perror(file);
	}
	skip_spaces(line);
	free(file);
	return (fd);
}

int	single_right(char **line)
{
	char	*file;
	int		fd;

	file = ft_calloc(1);
	(*line)++;
	skip_spaces(line);
	while (**line && **line != ' ')
		parse_chr(line, &file, NULL);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		g_data.status = 1;
		perror(file);
	}
	skip_spaces(line);
	free(file);
	return (fd);
}

void	add_redirect(t_cmd *cmd, char **line)
{
	if (!ft_strncmp(*line, "<<", 2))
	{
		cmd->input = double_left(line);
		if (cmd->input < 0)
			cmd->stop = 1;
	}
	else if (!ft_strncmp(*line, ">>", 2))
		cmd->output = double_right(line);
	else if (**line == '<')
		cmd->input = single_left(line);
	else if (**line == '>')
		cmd->output = single_right(line);
	if (cmd->input < 0 || cmd->output < 0)
		cmd->file_error = 1;
}


/*
term/input_1.c
*/
/*
**	проверяет строку на печатаемые символы
**	в данном контексте '\n' является печатаемым
*/

int	n_is_print(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) == 0 && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
**	отсекает от строки последний символ и возвращает новую строку
**	если отсечь нечего, то возвращается пустая строка
*/

char	*str_end(char *str)
{
	char	*new_str;
	int		str_size;
	int		i;

	if (str == NULL)
		return (ft_strdup(""));
	str_size = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * str_size);
	i = 0;
	while (str[i + 1] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

/*
**	соединяет две строки в одну команду
**	в случае неудачи, возвращает пустую строку
*/

char	*get_command(char *str, char *add)
{
	char	*command;

	command = ft_strjoin(str, add);
	if (command == NULL)
		command = ft_strdup(add);
	else
		free(str);
	free(add);
	return (command);
}

/*
**	дополняет команду, которая содержится
**	в истории, либо в основном вводе
*/

void	hist_or_command(char *buf)
{
	if (g_data.history.flag == 0)
	{
		g_data.history.command_print++;
		g_data.history.command
			= get_command(g_data.history.command, ft_strdup(buf));
	}
	if (g_data.history.flag == 1)
	{
		g_data.history.hist_print++;
		g_data.history.hist_end->content
			= get_command(g_data.history.hist_end->content, ft_strdup(buf));
	}
}

/*
**	главная функция ввода данных
*/

void	input(void)
{
	int		i;
	char	buf[4];

	print_message();
	g_data.history.command_print = 0;
	g_data.history.command = NULL;
	g_data.history.hist_buf = NULL;
	while (1)
	{
		i = read(0, buf, 3);
		buf[i] = '\0';
		if (!keys(buf) && n_is_print(buf) == 0)
		{
			write(1, buf, i);
			hist_or_command(buf);
		}
		control_characters(buf);
	}
	free(g_data.history.command);
	free(g_data.history.hist_buf);
}

/*
term/input_2.c
*/
void	main_input(void)
{
	g_data.history.command = str_end(g_data.history.command);
	if (g_data.history.command[0] != '\0')
	{
		hist_add_str(g_data.history.command);
		parse_cmd(g_data.history.command);
	}
	g_data.history.command_print = 0;
	dlist_end();
}

void	hist_input(void)
{
	g_data.history.hist_end->content
		= str_end(g_data.history.hist_end->content);
	if (((char *)(g_data.history.hist_end->content))[0] != '\0')
	{
		hist_add_str(g_data.history.hist_end->content);
		parse_cmd(g_data.history.hist_end->content);
	}
	free(g_data.history.hist_end->content);
	g_data.history.hist_end->content = ft_strdup(g_data.history.hist_buf);
	dlist_end();
}

/*
**	обработка клавиши enter
**	здесь str_end используется для отсечения '\n'
*/

static void	kenter(void)
{
	if (g_data.history.flag == 0)
		main_input();
	if (g_data.history.flag == 1)
		hist_input();
	free(g_data.history.command);
	g_data.history.command = NULL;
	print_message();
	g_data.history.flag = 0;
}

void	control_characters(char *str)
{
	if (ft_strncmp(str, "\4", 1) == 0)
	{
		if (g_data.history.flag == 0 && g_data.history.command_print > 0)
			ft_putstr_fd("\a", 1);
		else
			if (g_data.history.flag == 1 && g_data.history.hist_print > 0)
				ft_putstr_fd("\a", 1);
		else
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
	}
	if (ft_strncmp(str, "\f", 1) == 0)
	{
		tputs(tgetstr("cl", 0), 1, output_func);
		print_message();
		if (g_data.history.flag == 0)
			ft_putstr_fd(g_data.history.command, 1);
		if (g_data.history.flag == 1)
			ft_putstr_fd(g_data.history.hist_end->content, 1);
	}
	if (ft_strncmp(str, "\n", 1) == 0)
		kenter();
}


/*
term/keys.c
*/
void	kup(void)
{
	if (g_data.history.hist_end == NULL)
		ft_putstr_fd("\a", 1);
	if (g_data.history.hist_end)
	{
		tputs(tgetstr("rc", 0), 1, output_func);
		tputs(tgetstr("cd", 0), 1, output_func);
		if (g_data.history.hist_end->prev == NULL && g_data.history.flag == 1)
			ft_putstr_fd("\a", 1);
		if (g_data.history.hist_end->prev && g_data.history.flag == 1)
			g_data.history.hist_end = g_data.history.hist_end->prev;
		g_data.history.flag = 1;
		ft_putstr_fd(g_data.history.hist_end->content, 1);
		g_data.history.hist_print = ft_strlen(g_data.history.hist_end->content);
		if (g_data.history.hist_buf)
			free(g_data.history.hist_buf);
		g_data.history.hist_buf = ft_strdup(g_data.history.hist_end->content);
	}
}

void	kdown(void)
{
	tputs(tgetstr("rc", 0), 1, output_func);
	tputs(tgetstr("cd", 0), 1, output_func);
	if (g_data.history.hist_end && g_data.history.hist_end->next)
	{
		g_data.history.hist_end = g_data.history.hist_end->next;
		ft_putstr_fd(g_data.history.hist_end->content, 1);
		g_data.history.hist_print = ft_strlen(g_data.history.hist_end->content);
		if (g_data.history.hist_buf)
			free(g_data.history.hist_buf);
		g_data.history.hist_buf = ft_strdup(g_data.history.hist_end->content);
	}
	else
	{
		if (g_data.history.flag == 0)
			ft_putstr_fd("\a", 1);
		g_data.history.flag = 0;
		ft_putstr_fd(g_data.history.command, 1);
	}
}

void	kback(void)
{
	if (g_data.history.command_print <= 0 && g_data.history.hist_print <= 0)
		ft_putstr_fd("\a", 1);
	if (g_data.history.command_print > 0 && g_data.history.flag == 0)
	{
		tputs(tgetstr("le", 0), 1, output_func);
		tputs(tgetstr("dc", 0), 1, output_func);
		g_data.history.command_print--;
		g_data.history.command = str_end(g_data.history.command);
	}
	if (g_data.history.hist_print > 0 && g_data.history.flag == 1)
	{
		tputs(tgetstr("le", 0), 1, output_func);
		tputs(tgetstr("dc", 0), 1, output_func);
		g_data.history.hist_print--;
		g_data.history.hist_end->content
			= str_end(g_data.history.hist_end->content);
	}
}

int	keys(char *key)
{
	if (ft_strncmp(key, "\e[A", 3) == 0)
	{
		kup();
		return (1);
	}
	if (ft_strncmp(key, "\e[B", 3) == 0)
	{
		kdown();
		return (2);
	}
	if (ft_strncmp(key, "\177", 1) == 0)
	{
		kback();
		return (5);
	}
	if (ft_strncmp(key, "\e[C", 1) == 0)
		return (3);
	if (ft_strncmp(key, "\e[D", 1) == 0)
		return (4);
	return (0);
}


/*
term/prompt.c
*/

/*
**	возвращает количество строк в двумерном массиве
*/

int	arr_size(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	home_dir(char *message)
{
	ft_putstr_fd("\033[1;36m", 1);
	ft_putstr_fd(message, 1);
	write(1, ": ", 2);
	ft_putstr_fd("\033[0m", 1);
	tputs(tgetstr("sc", 0), 1, output_func);
	free(message);
}

/*
**	выводит приглашение к вводу
*/

void	print_message(void)
{
	char	*message;
	char	**spt_strs;
	int		i;

	message = getcwd(NULL, 0);
	if (message[0] == '/' && message[1] == '\0')
	{
		home_dir(message);
		return ;
	}
	spt_strs = ft_split(message, '/');
	free(message);
	ft_putstr_fd("\033[1;36m", 1);
	ft_putstr_fd(spt_strs[arr_size(spt_strs) - 1], 1);
	write(1, ": ", 2);
	ft_putstr_fd("\033[0m", 1);
	tputs(tgetstr("sc", 0), 1, output_func);
	i = 0;
	while (spt_strs[i])
	{
		free(spt_strs[i]);
		i++;
	}
	free(spt_strs);
}

/*
term/setup_term.c
*/
int	output_func(int c)
{
	int				i;

	i = write(1, &c, 1);
	return (i);
}

/*
**	1) get term struct
**	2) change this struct
**	3) save changes
**	4) apply this changes
*/

void	setup_term(void)
{
	struct termios	setup;
	char			*term;

	tcgetattr(0, &setup);
	setup.c_lflag &= (~ECHO);
	setup.c_lflag &= (~ICANON);
	tcsetattr(0, 0, &setup);
	tgetent(0, term = env_get_var("TERM"));
	free(term);
}

void	reset_term(void)
{
	char			*term;

	tcsetattr(0, 0, &g_data.termset);
	tgetent(0, term = env_get_var("TERM"));
	free(term);
}

/*
term/signals.c
*/

/*
** 0 - parent
** >0 - child
*/

void	main_input_re(void)
{
	g_data.history.flag = 0;
	if (g_data.history.command != NULL)
		free(g_data.history.command);
	g_data.history.command = NULL;
	g_data.history.command_print = 0;
	dlist_end();
}

void	hist_input_re(void)
{
	free(g_data.history.hist_end->content);
	g_data.history.hist_end->content = ft_strdup(g_data.history.hist_buf);
}

void	sig_int(int code)
{
	(void)code;
	if (g_data.sig_pid == 0)
	{
		write(1, "\n", 1);
		print_message();
		g_data.status = 1;
		if (g_data.history.flag == 1)
			hist_input_re();
		main_input_re();
	}
	if (g_data.sig_pid > 0)
		g_data.status = 130;
}

void	sig_quit(int code)
{
	(void)code;
	if (g_data.sig_pid == 0)
		ft_putstr_fd("\a", 1);
	if (g_data.sig_pid > 0)
		g_data.status = 131;
}

void	set_sig(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_data.status = 0;
	g_data.sig_pid = 0;
	set_sig();
	tcgetattr(0, &g_data.termset);
	setup_term();
	tputs(tgetstr("cl", 0), 1, output_func);
	ft_putstr_fd("\033[1;32mWELCOME TO SHELL\n\033[0m", 1);
	env_get(envp);
	shlvl_set();
	hist_create();
	input();
	dlist_free(g_data.history.hist_start);
	close(g_data.history.hist_fd);
	env_free(g_data.env);
}

#include "../includes/minishell.h"

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

void	tolower_builtin(t_data *cmd)
{
	if (!cmd->args)
		return ;
	while (cmd && cmd->args)
	{
		cmp_builtin(cmd->args[0]);
		cmd = cmd->next;
	}
}

void	dol_sign_status(char **line, char **fullline)
{
	char	*tmp_status;

	tmp_status = ft_itoa(g_main.status);
	*fullline = ft_strnjoin(*fullline, tmp_status, ft_strlen(tmp_status));
	free(tmp_status);
	(*line)++;
	g_main.status = 0;
}

void	*get_path(t_data *cmd, char **envp)
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
		g_main.status = 1;
		return (array_free((void **)path));
	}
	if ((checker_file(cmd)) == -1)
		return (array_free((void **)path));
	else if ((checker_file(cmd)) == 1)
		if (!checker_path(path, cmd))
			return (array_free((void **)path));
	array_free((void **)path);
	return ((void *)1);
}

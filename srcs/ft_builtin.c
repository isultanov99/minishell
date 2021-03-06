/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 18:23:17 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/17 18:23:20 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	ft_export(t_data *cmd)
{
	int		fd;
	char	**params;
	int		i;

	fd = cmd->output;
	params = cmd->args;
	i = 1;
	if (params[i] == 0)
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

int	ft_pwd(t_data *cmd)
{
	int		fd;
	char	**params;
	char	*pwd_path;

	fd = cmd->output;
	params = cmd->args;
	pwd_path = getcwd(NULL, 0);
	if (pwd_path == 0)
		return (1);
	ft_putstr_fd(pwd_path, fd);
	write(fd, "\n", 1);
	free(pwd_path);
	return (0);
}

int	builtin_handler(t_data *cmd)
{
	if (!cmd->args)
		return (0);
	if (cmd->file_error)
		return (1);
	if (ft_strcmp("cd", cmd->args[0]) == 0)
		g_main.status = ft_cd(cmd);
	else if (ft_strcmp("echo", cmd->args[0]) == 0)
		g_main.status = ft_echo(cmd);
	else if (ft_strcmp("env", cmd->args[0]) == 0)
		g_main.status = ft_env(cmd);
	else if (ft_strcmp("exit", cmd->args[0]) == 0)
		g_main.status = ft_exit(cmd);
	else if (ft_strcmp("export", cmd->args[0]) == 0)
		g_main.status = ft_export(cmd);
	else if (ft_strcmp("pwd", cmd->args[0]) == 0)
		g_main.status = ft_pwd(cmd);
	else if (ft_strcmp("unset", cmd->args[0]) == 0)
		g_main.status = ft_unset(cmd);
	else
		return (0);
	return (1);
}

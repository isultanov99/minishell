/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 18:23:00 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/17 18:55:45 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_print_error(char *path, int fd)
{
	write(fd, "cd: ", 4);
	ft_putstr_fd(path, fd);
	write(fd, ": ", 2);
	ft_putstr_fd(strerror(errno), fd);
	write(fd, "\n", 1);
}

int	cd_without_arg(int fd, char *pwd_path)
{
	char	*home_path;

	home_path = getenv("HOME");
	if (home_path == 0)
	{
		ft_putstr_fd("cd: HOME not set\n", fd);
		return (1);
	}
	if (chdir(home_path) == 0)
	{
		change_env_var("OLDPWD", pwd_path);
		change_env_var("PWD", home_path);
	}
	else
	{
		cd_print_error(home_path, fd);
		return (1);
	}
	return (0);
}

int	cd_with_arg(int fd, char *path, char *cwd_path, char *pwd_path)
{
	if (strcmp("/", cwd_path) == 0)
		return (0);
	if (chdir(path) == 0)
	{
		cwd_path = getcwd(NULL, 0);
		change_env_var("OLDPWD", pwd_path);
		change_env_var("PWD", cwd_path);
	}
	else
	{
		cd_print_error(path, fd);
		return (1);
	}
	return (0);
}

int	ft_cd(t_data *cmd)
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
	if (path)
		result = cd_with_arg(fd, path, cwd_path, pwd_path);
	else
		result = cd_without_arg(fd, pwd_path);
	free(cwd_path);
	return (result);
}

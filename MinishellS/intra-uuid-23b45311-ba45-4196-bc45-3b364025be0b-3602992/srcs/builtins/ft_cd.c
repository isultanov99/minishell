/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:18:52 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:18:54 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_print_error(char *path, int fd)
{
	write(fd, "cd: ", 4);
	ft_putstr_fd(path, fd);
	write(fd, ": ", 2);
	ft_putstr_fd(strerror(errno), fd);
	write(fd, "\n", 1);
}

int	without_arg(int fd, char *pwd_path)
{
	char	*home_path;

	home_path = env_get_var("HOME");
	if (home_path == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", fd);
		return (1);
	}
	if (chdir(home_path) == 0)
	{
		env_change_var("OLDPWD", pwd_path);
		env_change_var("PWD", home_path);
		free(home_path);
	}
	else
	{
		cd_print_error(home_path, fd);
		free(home_path);
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

int	ft_cd(t_cmd *cmd)
{
	int		fd;
	char	*path;
	char	*cwd_path;
	char	*pwd_path;
	int		ret;

	fd = cmd->output;
	path = cmd->args[1];
	cwd_path = getcwd(NULL, 0);
	pwd_path = env_get_var("PWD");
	if (path == NULL)
		ret = without_arg(fd, pwd_path);
	else
		ret = with_arg(fd, path, cwd_path, pwd_path);
	free(cwd_path);
	free(pwd_path);
	return (ret);
}

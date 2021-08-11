/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:19:27 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:19:27 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

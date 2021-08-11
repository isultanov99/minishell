/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:19:00 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:19:00 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	проверяет, является ли строка опцией
**	возвращает 0, если это опция, иначе - 1
*/

int	echo_opt(char *str)
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
	int		opt;

	fd = cmd->output;
	params = cmd->args;
	i = 1;
	if (check_params(params[i], fd) == 1)
		return (0);
	opt = 0;
	if (echo_opt(params[i]) == 0)
		opt = 1;
	while (params[i] && echo_opt(params[i]) == 0)
		i++;
	while (params[i])
	{
		ft_putstr_fd(params[i], fd);
		if (params[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (opt == 0)
		write(fd, "\n", 1);
	return (0);
}

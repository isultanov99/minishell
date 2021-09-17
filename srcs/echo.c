/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 18:23:04 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/17 18:23:05 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	checker_params(char *param, int fd)
{
	if (param == 0)
	{
		write(fd, "\n", 1);
		return (1);
	}
	return (0);
}

int	ft_echo(t_data *cmd)
{
	int		fd;
	char	**params;
	int		i;
	int		option;

	fd = cmd->output;
	params = cmd->args;
	i = 1;
	if (checker_params(params[i], fd) == 1)
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

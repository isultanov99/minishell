/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 18:23:42 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/17 18:23:44 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	ft_exit(t_data *cmd)
{
	int		fd;
	char	**params;
	int		exit_code;

	fd = cmd->output;
	params = cmd->args;
	if (params[1] == 0)
		ft_putstr_fd("exit\n", fd);
	if (params[1] == 0)
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

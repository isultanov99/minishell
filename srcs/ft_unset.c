/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:16:09 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/17 17:58:06 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	var_print_error(int fd, char *var)
{
	write(fd, "export: `", 9);
	ft_putstr_fd(var, fd);
	write(fd, "': not a valid identifier\n", 26);
}

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

int	ft_unset(t_data *cmd)
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

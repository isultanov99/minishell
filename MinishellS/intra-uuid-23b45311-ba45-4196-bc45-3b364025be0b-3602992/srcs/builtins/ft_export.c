/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:19:23 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:19:23 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

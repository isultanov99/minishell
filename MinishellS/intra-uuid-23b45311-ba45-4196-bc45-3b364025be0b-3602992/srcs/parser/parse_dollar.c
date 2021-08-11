/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 13:06:44 by natali            #+#    #+#             */
/*   Updated: 2021/08/04 13:07:08 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_status(char **line, char **superline)
{
	char	*tmp_status;

	tmp_status = ft_itoa(g_data.status);
	*superline = ft_strnjoin(*superline, tmp_status, ft_strlen(tmp_status));
	free(tmp_status);
	(*line)++;
	g_data.status = 0;
}

void	dollar_get_value(char **line, char **superline, int len)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	key = ft_substr(*line, 0, len);
	value = env_get_var(key);
	if (value && *value)
		*superline = ft_strnjoin(*superline, value, ft_strlen(value));
	free(key);
	free(value);
	*line += len;
}

void	dollar(char **line, char **superline)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	(*line)++;
	if (**line == '?')
	{
		dollar_status(line, superline);
		return ;
	}
	else if (ft_isdigit(**line))
	{
		(*line)++;
		return ;
	}
	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '\''
		&& (*line)[i] != '\"')
		i++;
	if (!i)
	{
		*superline = ft_strnjoin(*superline, "$", 1);
		return ;
	}
	dollar_get_value(line, superline, i);
}

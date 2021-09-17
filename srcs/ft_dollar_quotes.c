/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:10:21 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/17 19:10:23 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dol_sign_get_value(char **line, char **fullline, int len)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	key = ft_substr(*line, 0, len);
	value = env_get_var(key);
	if (value && *value)
		*fullline = ft_strnjoin(*fullline, value, ft_strlen(value));
	free(key);
	free(value);
	*line += len;
}

void	dol_sign(char **line, char **fullline)
{
	int		i;

	i = 0;
	(*line)++;
	if (**line == '?')
	{
		dol_sign_status(line, fullline);
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
		*fullline = ft_strnjoin(*fullline, "$", 1);
		return ;
	}
	dol_sign_get_value(line, fullline, i);
}

void	space_skipper(char **line)
{
	if (*line)
	{
		while (**line && **line == ' ')
			(*line)++;
	}
}

void	squotes(char **line, char **fullline, t_data *cmd)
{
	*fullline = ft_strnjoin(*fullline, *line + 1,
			ft_strlen_chr(*line + 1, '\''));
	*line += ft_strlen_chr(*line + 1, '\'') + 2;
	if (cmd && !**line && !**fullline)
		end_of_args(line, fullline, cmd, 0);
}

void	dquotes(char **line, char **fullline, t_data *cmd)
{
	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '$')
			dol_sign(line, fullline);
		else
		{
			*fullline = ft_strnjoin(*fullline, *line, 1);
			(*line)++;
		}
	}
	if (**line)
		(*line)++;
	if (cmd && !**fullline && !**line)
		end_of_args(line, fullline, cmd, 0);
}

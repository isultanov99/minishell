/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 16:37:14 by natali            #+#    #+#             */
/*   Updated: 2021/08/04 20:18:51 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char **line)
{
	if (*line)
	{
		while (**line && **line == ' ')
			(*line)++;
	}
}

void	single_quotes(char **line, char **superline, t_cmd *cmd)
{
	*superline = ft_strnjoin(*superline, *line + 1,
			ft_strlen_chr(*line + 1, '\''));
	*line += ft_strlen_chr(*line + 1, '\'') + 2;
	if (cmd && !**line && !**superline)
		end_of_args(line, superline, cmd, 0);
}

void	double_quotes(char **line, char **superline, t_cmd *cmd)
{
	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '$')
			dollar(line, superline);
		else
		{
			*superline = ft_strnjoin(*superline, *line, 1);
			(*line)++;
		}
	}
	if (**line)
		(*line)++;
	if (cmd && !**superline && !**line)
		end_of_args(line, superline, cmd, 0);
}

void	simple_chr(char **line, char **superline)
{
	*superline = ft_strnjoin(*superline, *line, 1);
	(*line)++;
}

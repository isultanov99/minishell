/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 10:33:42 by natali            #+#    #+#             */
/*   Updated: 2021/08/04 21:02:33 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_right(char **line)
{
	char	*file;
	int		fd;

	file = ft_calloc(1);
	*line = *line + 2;
	skip_spaces(line);
	while (**line && **line != ' ')
		parse_chr(line, &file, NULL);
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
	{
		g_data.status = 1;
		perror(file);
	}
	skip_spaces(line);
	free(file);
	return (fd);
}

int	single_left(char **line)
{
	char	*file;
	int		fd;

	file = ft_calloc(1);
	(*line)++;
	skip_spaces(line);
	while (**line && **line != ' ')
		parse_chr(line, &file, NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		g_data.status = 1;
		perror(file);
	}
	skip_spaces(line);
	free(file);
	return (fd);
}

int	single_right(char **line)
{
	char	*file;
	int		fd;

	file = ft_calloc(1);
	(*line)++;
	skip_spaces(line);
	while (**line && **line != ' ')
		parse_chr(line, &file, NULL);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		g_data.status = 1;
		perror(file);
	}
	skip_spaces(line);
	free(file);
	return (fd);
}

void	add_redirect(t_cmd *cmd, char **line)
{
	if (!ft_strncmp(*line, "<<", 2))
	{
		cmd->input = double_left(line);
		if (cmd->input < 0)
			cmd->stop = 1;
	}
	else if (!ft_strncmp(*line, ">>", 2))
		cmd->output = double_right(line);
	else if (**line == '<')
		cmd->input = single_left(line);
	else if (**line == '>')
		cmd->output = single_right(line);
	if (cmd->input < 0 || cmd->output < 0)
		cmd->file_error = 1;
}

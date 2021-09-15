/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:17:21 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/15 18:19:40 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dleft(char **line)
{
	int		heredoc_fd;
	char	*stop;
	int		status;

	stop = ft_calloc(1);
	status = 0;
	*line = *line + 2;
	skip_spaces(line);
	while (**line && **line != ' ')
		parse_chr(line, &stop, NULL);
	heredoc_fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if ((get_input(stop, heredoc_fd)) > 0)
	{
		free(stop);
		setup_term();
		return (-1);
	}
	heredoc_fd = open(".heredoc", O_RDONLY);
	skip_spaces(line);
	free(stop);
	return (heredoc_fd);
}

int	dright(char **line)
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
		g_main.status = 1;
		perror(file);
	}
	skip_spaces(line);
	free(file);
	return (fd);
}

int	sleft(char **line)
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
		g_main.status = 1;
		perror(file);
	}
	skip_spaces(line);
	free(file);
	return (fd);
}

int	sright(char **line)
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
		g_main.status = 1;
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
		cmd->input = dleft(line);
		if (cmd->input < 0)
			cmd->stop = 1;
	}
	else if (!ft_strncmp(*line, ">>", 2))
		cmd->output = dright(line);
	else if (**line == '>')
		cmd->output = sright(line);
	else if (**line == '<')
		cmd->input = sleft(line);
	if (cmd->input < 0 || cmd->output < 0)
		cmd->file_error = 1;
}

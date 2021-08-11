/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 14:40:21 by natali            #+#    #+#             */
/*   Updated: 2021/08/04 18:32:33 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int code)
{
	pid_t	id;

	(void)code;
	ft_putstr_fd("\n", 1);
	id = getpid();
	kill(id, SIGKILL);
}

void	sigquit_handler(int code)
{
	(void)code;
}

void	add_heredoc(char *end, int heredoc_fd)
{
	char	*input;

	input = "\0";
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			ft_putstr_fd("\b\b", 2);
			exit(0);
		}
		if (ft_strcmp(input, end))
		{
			ft_putstr_fd(input, heredoc_fd);
			ft_putstr_fd("\n", heredoc_fd);
		}
		else
			exit(0);
	}
}

int	get_input(char *stop, int heredoc_fd)
{
	int	status;

	reset_term();
	g_data.sig_pid = fork();
	if (g_data.sig_pid == 0)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, &sigquit_handler);
		add_heredoc(stop, heredoc_fd);
	}
	else if (g_data.sig_pid < 0)
		exit(EXIT_FAILURE);
	wait(&status);
	g_data.sig_pid = 0;
	close(heredoc_fd);
	status = WTERMSIG(status);
	return (status);
}

int	double_left(char **line)
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

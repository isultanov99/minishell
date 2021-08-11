/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 16:39:03 by natali            #+#    #+#             */
/*   Updated: 2021/08/02 14:38:59 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_cmd *cmd)
{
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd->next)
	{
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
		cmd = cmd->next;
	}
}

void	link_pipes(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->next)
		{
			if (cmd->next->input == STDIN_FILENO)
				cmd->next->input = cmd->pipe_fd[0];
			if (cmd->output == STDOUT_FILENO)
				cmd->output = cmd->pipe_fd[1];
		}
		cmd = cmd->next;
	}
}

void	add_pipe(t_cmd *cmd, char **line)
{
	(*line)++;
	skip_spaces(line);
	if ((pipe(cmd->pipe_fd)) == -1)
	{
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}
}

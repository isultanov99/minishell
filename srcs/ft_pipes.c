/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 21:21:27 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/15 21:22:58 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	add_pipe(t_cmd *cmd, char **line)
{
	(*line)++;
	skip_spaces(line);
	if ((pipe(cmd->pipe_fd)) == -1)
	{
		perror("Pipe error");
		exit(1);
	}
}

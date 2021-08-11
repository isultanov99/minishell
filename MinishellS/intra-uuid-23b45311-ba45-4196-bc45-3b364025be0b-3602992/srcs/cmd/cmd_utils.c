/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 16:03:18 by natali            #+#    #+#             */
/*   Updated: 2021/08/02 23:30:00 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmdlen(t_cmd *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_cmd	*last_cmd(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	put_back_cmd(t_cmd **start, t_cmd *new)
{
	t_cmd	*last;

	if (!*start)
	{
		*start = new;
		return ;
	}
	last = last_cmd(*start);
	last->next = new;
	new->prev = last;
}

int	check_cmd(t_cmd *start)
{
	while (start)
	{
		if (start->stop == 1)
			return (1);
		start = start->next;
	}
	return (0);
}

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->input = STDIN_FILENO;
	cmd->output = STDOUT_FILENO;
	cmd->stop = 0;
	cmd->file_error = 0;
	return (cmd);
}

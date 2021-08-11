/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:11:58 by natali            #+#    #+#             */
/*   Updated: 2021/08/04 21:03:49 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_of_args(char **line, char **superline, t_cmd *cmd, int code)
{
	char	*tmp;

	if (!code)
		cmd->args = ft_realloc_arr(cmd->args, arr_len((void **)cmd->args),
				*superline);
	skip_spaces(line);
	if (!**line || code == 1)
	{
		free(*superline);
		*superline = NULL;
	}
	else
	{
		tmp = *superline;
		*superline = ft_strdup("\0");
		free (tmp);
		skip_spaces(line);
	}
}

void	parse_chr(char **line, char **superline, t_cmd *cmd)
{
	if (**line && **line == '\'')
		single_quotes(line, superline, cmd);
	else if (**line && **line == '\"')
		double_quotes(line, superline, cmd);
	else if (**line && **line == '$')
		dollar(line, superline);
	else if (**line && **line != '|' && **line != '<'
		&& **line != '>' && **line != ' ')
		simple_chr(line, superline);
}

int	parse_loop(t_cmd *cmd, char **line, char **superline)
{
	if (**line)
		parse_chr(line, superline, cmd);
	if (**line && (**line == '<' || **line == '>'))
	{
		add_redirect(cmd, line);
		if (!**line)
		{
			if (*superline)
				if (!**superline)
					end_of_args(line, superline, cmd, 1);
			end_of_args(line, superline, cmd, 0);
			return (1);
		}
	}
	if (**line && **line == '|')
	{
		add_pipe(cmd, line);
		if (*(*line - 1) != ' ')
			end_of_args(line, superline, cmd, 0);
		end_of_args(line, superline, cmd, 1);
		return (1);
	}
	if (**line && **line == ' ')
		end_of_args(line, superline, cmd, 0);
	return (0);
}

t_cmd	*parse_str(t_cmd *cmd, char **line)
{
	char		*superline;

	cmd = cmd_init();
	superline = ft_calloc(1);
	skip_spaces(line);
	while (**line)
		if ((parse_loop(cmd, line, &superline)))
			return (cmd);
	if (superline)
		if (!*superline)
			end_of_args(line, &superline, cmd, 1);
	end_of_args(line, &superline, cmd, 0);
	return (cmd);
}

void	parse_cmd(char *line)
{
	t_cmd		*start;
	t_cmd		*cmd;
	char		*superline;

	start = NULL;
	while (1)
	{
		cmd = parse_str(cmd, &line);
		put_back_cmd(&start, cmd);
		if (!*line)
			break ;
	}
	if (!(check_cmd(start)))
	{
		link_pipes(start);
		tolower_builtin(start);
		exec_cmd(start);
	}
	else
		free_cmd(start);
}

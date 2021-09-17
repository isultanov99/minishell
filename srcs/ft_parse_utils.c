/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:10:44 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/17 19:10:45 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	end_of_args(char **line, char **fullline, t_data *cmd, int code)
{
	char	*tmp;

	if (!code)
		cmd->args = ft_realloc_arr(cmd->args, arr_len((void **)cmd->args),
				*fullline);
	space_skipper(line);
	if (!**line || code == 1)
	{
		free(*fullline);
		*fullline = NULL;
	}
	else
	{
		tmp = *fullline;
		*fullline = ft_strdup("\0");
		free (tmp);
		space_skipper(line);
	}
}

void	parse_chr(char **line, char **fullline, t_data *cmd)
{
	if (**line && **line == '\'')
		squotes(line, fullline, cmd);
	else if (**line && **line == '\"')
		dquotes(line, fullline, cmd);
	else if (**line && **line == '$')
		dol_sign(line, fullline);
	else if (**line && **line != '|' && **line != '<'
		&& **line != '>' && **line != ' ')
	{
		*fullline = ft_strnjoin(*fullline, *line, 1);
		(*line)++;
	}
}

int	parse_loop(t_data *cmd, char **line, char **fullline)
{
	if (**line)
		parse_chr(line, fullline, cmd);
	if (**line && (**line == '<' || **line == '>'))
	{
		add_redirect(cmd, line);
		if (!**line)
		{
			if (*fullline)
				if (!**fullline)
					end_of_args(line, fullline, cmd, 1);
			end_of_args(line, fullline, cmd, 0);
			return (1);
		}
	}
	if (**line && **line == '|')
	{
		add_pipe(cmd, line);
		if (*(*line - 1) != ' ')
			end_of_args(line, fullline, cmd, 0);
		end_of_args(line, fullline, cmd, 1);
		return (1);
	}
	if (**line && **line == ' ')
		end_of_args(line, fullline, cmd, 0);
	return (0);
}

t_data	*parse_str(t_data *cmd, char **line)
{
	char		*fullline;

	cmd = cmd_init();
	fullline = ft_calloc(1);
	space_skipper(line);
	while (**line)
		if ((parse_loop(cmd, line, &fullline)))
			return (cmd);
	if (fullline)
		if (!*fullline)
			end_of_args(line, &fullline, cmd, 1);
	end_of_args(line, &fullline, cmd, 0);
	return (cmd);
}

void	parse_cmd(char *line)
{
	t_data		*start;
	t_data		*cmd;

	cmd = NULL;
	start = NULL;
	while (1)
	{
		cmd = parse_str(cmd, &line);
		put_back_cmd(&start, cmd);
		if (!*line)
			break ;
	}
	if (!(checker_cmd(start)))
	{
		link_pipes(start);
		tolower_builtin(start);
		exec_cmd(start);
	}
	else
		free_cmd(start);
}

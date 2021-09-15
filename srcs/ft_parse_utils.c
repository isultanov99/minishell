#include "../includes/minishell.h"

void	end_of_args(char **line, char **superline, t_cmd *cmd, int code)
{
	char	*tmp;

	if (!code)
		cmd->args = ft_realloc_arr(cmd->args, arr_len((void **)cmd->args),
				*superline);
	space_skipper(line);
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
		space_skipper(line);
	}
}

void	parse_chr(char **line, char **superline, t_cmd *cmd)
{
	if (**line && **line == '\'')
		squotes(line, superline, cmd);
	else if (**line && **line == '\"')
		dquotes(line, superline, cmd);
	else if (**line && **line == '$')
		dol_sign(line, superline);
	else if (**line && **line != '|' && **line != '<'
		&& **line != '>' && **line != ' ')
	{
		*superline = ft_strnjoin(*superline, *line, 1);
		(*line)++;
	}
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
	space_skipper(line);
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

	cmd = NULL;
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

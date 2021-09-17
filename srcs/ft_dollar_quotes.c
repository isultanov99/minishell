#include "../includes/minishell.h"

void	dol_sign_get_value(char **line, char **superline, int len)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	key = ft_substr(*line, 0, len);
	value = env_get_var(key);
	if (value && *value)
		*superline = ft_strnjoin(*superline, value, ft_strlen(value));
	free(key);
	free(value);
	*line += len;
}

void	dol_sign(char **line, char **superline)
{
	int		i;

	i = 0;
	(*line)++;
	if (**line == '?')
	{
		dol_sign_status(line, superline);
		return ;
	}
	else if (ft_isdigit(**line))
	{
		(*line)++;
		return ;
	}
	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '\''
		&& (*line)[i] != '\"')
		i++;
	if (!i)
	{
		*superline = ft_strnjoin(*superline, "$", 1);
		return ;
	}
	dol_sign_get_value(line, superline, i);
}

void	space_skipper(char **line)
{
	if (*line)
	{
		while (**line && **line == ' ')
			(*line)++;
	}
}

void	squotes(char **line, char **superline, t_data *cmd)
{
	*superline = ft_strnjoin(*superline, *line + 1,
			ft_strlen_chr(*line + 1, '\''));
	*line += ft_strlen_chr(*line + 1, '\'') + 2;
	if (cmd && !**line && !**superline)
		end_of_args(line, superline, cmd, 0);
}

void	dquotes(char **line, char **superline, t_data *cmd)
{
	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '$')
			dol_sign(line, superline);
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

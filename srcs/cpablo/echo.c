#include "../../includes/minishell.h"

int	echo_aux(char *str)
{
	int		i;

	i = 0;
	if (str[i] != '-')
		return (1);
	i = 1;
	if (str[i] != 'n')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	check_params(char *param, int fd)
{
	if (param == 0)
	{
		write(fd, "\n", 1);
		return (1);
	}
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
	int		fd;
	char	**params;
	int		i;
	int		option;

	fd = cmd->output;
	params = cmd->args;
	i = 1;
	if (check_params(params[i], fd) == 1)
		return (0);
	option = 0;
	if (echo_aux(params[i]) == 0)
		option = 1;
	while (params[i] && echo_aux(params[i]) == 0)
		i++;
	while (params[i])
	{
		ft_putstr_fd(params[i], fd);
		if (params[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (option == 0)
		write(fd, "\n", 1);
	return (0);
}

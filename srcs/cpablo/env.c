#include "../../includes/minishell.h"
int	ft_env(t_cmd *cmd)
{
	int	fd;

	fd = cmd->output;
	env_print(fd);
	return (0);
}

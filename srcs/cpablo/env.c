#include "../../includes/minishell.h"

int	ft_env(t_cmd *cmd)
{
	int	fd;

	fd = cmd->output;
	env_print(fd);
	return (0);
}

void	env_print(int fd)
{
	t_list	*cp;

	cp = g_main.env;
	while (cp)
	{
		if (ft_strchr((char *)cp->content, '='))
		{
			ft_putstr_fd((char *)cp->content, fd);
			write(fd, "\n", 1);
		}
		cp = cp->next;
	}
}

void	env_get(char **envp)
{
	t_list	*list;
	int		i;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	g_main.env = list;
}

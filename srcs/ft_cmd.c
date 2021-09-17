#include "../includes/minishell.h"

void	put_back_cmd(t_data **start, t_data *new)
{
	t_data	*last;

	if (!*start)
	{
		*start = new;
		return ;
	}
	last = last_data(*start);
	last->next = new;
	new->prev = last;
}

int	checker_cmd(t_data *start)
{
	while (start)
	{
		if (start->stop == 1)
			return (1);
		start = start->next;
	}
	return (0);
}

t_data	*cmd_init(void)
{
	t_data	*cmd;

	cmd = (t_data *)malloc(sizeof(t_data));
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

void	fork_cmd_routine(t_data *cmd)
{
	char	**tmp;

	tmp = envp_arr();
	dup2(cmd->input, STDIN_FILENO);
	dup2(cmd->output, STDOUT_FILENO);
	close_pipes(cmd);
	if (!(get_path(cmd, tmp)))
		exit(g_main.status);
	if (cmd->file_error)
		exit(g_main.status);
	g_main.status = execve(cmd->path, cmd->args, tmp);
	ft_free_array((void **)tmp);
	if (g_main.status < 0)
	{
		if (errno == ENOEXEC)
			exit(0);
		else if (errno == EACCES)
		{
			perror(cmd->args[0]);
			exit(126);
		}
		else
			perror(cmd->args[0]);
	}
	exit (g_main.status);
}

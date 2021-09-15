#include "../includes/minishell.h"

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

void	fork_cmd_routine(t_cmd *cmd)
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

void	scmd(t_cmd *cmd)
{
	int		status;

	if (!(choose_builtin(cmd)))
	{
		g_main.sig_pid = fork();
		if (g_main.sig_pid == 0)
			fork_cmd_routine(cmd);
		else if (g_main.sig_pid < 0)
			exit(1);
		wait(&status);
		if (g_main.status != 130 && g_main.status != 131)
			g_main.status = WEXITSTATUS(status);
		g_main.sig_pid = 0;
	}
}

void	mcmd(t_cmd *cmd)
{
	int		status;

	while (cmd)
	{
		g_main.sig_pid = fork();
		if (g_main.sig_pid == 0)
		{
			if (!(choose_builtin(cmd)))
				fork_cmd_routine(cmd);
			else
				exit(g_main.status);
		}
		else if (g_main.sig_pid < 0)
			exit(1);
		if (!cmd->next)
			close_pipes(cmd);
		cmd = cmd->next;
	}
	while (wait(&status) != -1 && errno != ECHILD)
		g_main.status = WEXITSTATUS(status);
	g_main.sig_pid = 0;
}

void	exec_cmd(t_cmd *cmd)
{
	if (cmd->args)
	{
		reset_term();
		if (!cmd->next)
			scmd(cmd);
		else
			mcmd(cmd);
		setup_term();
	}
	free_cmd(cmd);
}


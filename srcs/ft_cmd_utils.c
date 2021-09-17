#include "../includes/minishell.h"

void	scmd(t_data *cmd)
{
	int		status;

	if (!(builtin_handler(cmd)))
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

void	mcmd(t_data *cmd)
{
	int		status;

	while (cmd)
	{
		g_main.sig_pid = fork();
		if (g_main.sig_pid == 0)
		{
			if (!(builtin_handler(cmd)))
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

void	exec_cmd(t_data *cmd)
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

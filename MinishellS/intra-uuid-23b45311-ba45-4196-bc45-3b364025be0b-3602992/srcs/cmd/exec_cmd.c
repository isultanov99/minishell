/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:43:05 by natali            #+#    #+#             */
/*   Updated: 2021/08/07 21:06:01 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	choose_builin(t_cmd *cmd)
{
	if (!cmd->args)
		return (0);
	if (cmd->file_error)
		return (1);
	if (ft_strcmp("echo", cmd->args[0]) == 0)
		g_data.status = ft_echo(cmd);
	else if (ft_strcmp("cd", cmd->args[0]) == 0)
		g_data.status = ft_cd(cmd);
	else if (ft_strcmp("pwd", cmd->args[0]) == 0)
		g_data.status = ft_pwd(cmd);
	else if (ft_strcmp("export", cmd->args[0]) == 0)
		g_data.status = ft_export(cmd);
	else if (ft_strcmp("unset", cmd->args[0]) == 0)
		g_data.status = ft_unset(cmd);
	else if (ft_strcmp("env", cmd->args[0]) == 0)
		g_data.status = ft_env(cmd);
	else if (ft_strcmp("exit", cmd->args[0]) == 0)
		g_data.status = ft_exit(cmd);
	else
		return (0);
	return (1);
}

void	fork_cmd_routine(t_cmd *cmd)
{
	char	**tmp;

	tmp = ft_envp_arr();
	dup2(cmd->input, STDIN_FILENO);
	dup2(cmd->output, STDOUT_FILENO);
	close_pipes(cmd);
	if (!(get_path(cmd, tmp)))
		exit(g_data.status);
	if (cmd->file_error)
		exit(g_data.status);
	g_data.status = execve(cmd->path, cmd->args, tmp);
	ft_free_array((void **)tmp);
	if (g_data.status < 0)
	{
		if (errno == ENOEXEC)
			exit(EXIT_SUCCESS);
		else if (errno == EACCES)
		{
			perror(cmd->args[0]);
			exit(126);
		}
		else
			perror(cmd->args[0]);
	}
	exit (g_data.status);
}

void	single_cmd(t_cmd *cmd)
{
	int		status;

	if (!choose_builin(cmd))
	{
		g_data.sig_pid = fork();
		if (g_data.sig_pid == 0)
			fork_cmd_routine(cmd);
		else if (g_data.sig_pid < 0)
			exit(EXIT_FAILURE);
		wait(&status);
		if (g_data.status != 130 && g_data.status != 131)
			g_data.status = WEXITSTATUS(status);
		g_data.sig_pid = 0;
	}
}

void	multi_cmd(t_cmd *cmd)
{
	int		status;

	while (cmd)
	{
		g_data.sig_pid = fork();
		if (g_data.sig_pid == 0)
		{
			if (!choose_builin(cmd))
				fork_cmd_routine(cmd);
			else
				exit(g_data.status);
		}
		else if (g_data.sig_pid < 0)
			exit(EXIT_FAILURE);
		if (!cmd->next)
			close_pipes(cmd);
		cmd = cmd->next;
	}
	while (wait(&status) != -1 && errno != ECHILD)
		g_data.status = WEXITSTATUS(status);
	g_data.sig_pid = 0;
}

void	exec_cmd(t_cmd *cmd)
{
	if (cmd->args)
	{
		reset_term();
		if (!cmd->next)
			single_cmd(cmd);
		else
			multi_cmd(cmd);
		setup_term();
	}
	free_cmd(cmd);
}

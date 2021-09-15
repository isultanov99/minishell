/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:14:29 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/15 20:14:53 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	choose_builtin(t_cmd *cmd)
{
	if (!cmd->args)
		return (0);
	if (cmd->file_error)
		return (1);
	if (ft_strcmp("cd", cmd->args[0]) == 0)
		g_main.status = ft_cd(cmd);
	else if (ft_strcmp("echo", cmd->args[0]) == 0)
		g_main.status = ft_echo(cmd);
	else if (ft_strcmp("env", cmd->args[0]) == 0)
		g_main.status = ft_env(cmd);
	else if (ft_strcmp("exit", cmd->args[0]) == 0)
		g_main.status = ft_exit(cmd);
	else if (ft_strcmp("export", cmd->args[0]) == 0)
		g_main.status = ft_export(cmd);
	else if (ft_strcmp("pwd", cmd->args[0]) == 0)
		g_main.status = ft_pwd(cmd);
	else if (ft_strcmp("unset", cmd->args[0]) == 0)
		g_main.status = ft_unset(cmd);
	else
		return (0);
	return (1);
}

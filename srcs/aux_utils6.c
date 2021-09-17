/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utils6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:11:18 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/17 19:11:19 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*path_name(char *path, char *cmd_name, t_data *cmd)
{
	struct stat	buff;
	char		*new;

	new = ft_strdup(path);
	new = ft_strnjoin(new, "/", 1);
	new = ft_strnjoin(new, cmd_name, ft_strlen(cmd_name));
	if ((stat(new, &buff)) == 0)
	{
		cmd->path = ft_strdup(new);
		free (new);
		return ((void *)1);
	}
	free (new);
	return (NULL);
}

int	checker_path(char **path, t_data *cmd)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if ((path_name(path[i], cmd->args[0], cmd)))
			return (1);
		i++;
	}
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	g_main.status = 127;
	return (0);
}

int	checker_file(t_data *cmd)
{
	struct stat	buff;

	if ((ft_strchr(cmd->args[0], '/')))
	{
		if ((stat(cmd->args[0], &buff)) < 0)
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_main.status = 127;
			return (-1);
		}
		else if (S_ISDIR(buff.st_mode))
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			g_main.status = 126;
			return (-1);
		}
		else
		{
			cmd->path = ft_strdup(cmd->args[0]);
			return (0);
		}
	}
	return (1);
}

void	free_cmd(t_data *cmd)
{
	t_data	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->path)
			free(cmd->path);
		if (cmd->args)
			array_free((void **)cmd->args);
		free (cmd);
		cmd = tmp;
	}
}

void	list_free(t_list *list)
{
	t_list	*mind;

	while (list)
	{
		mind = list->next;
		free(list->content);
		free(list);
		list = mind;
	}
}

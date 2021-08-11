/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:22:28 by natali            #+#    #+#             */
/*   Updated: 2021/08/04 15:24:03 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_tolower(char *str)
{
	char	*copy;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	i = -1;
	len = ft_strlen(str);
	copy = (char *)malloc(sizeof(char) * (len + 1));
	ft_bzero((void *)copy, len + 1);
	while (++i < len)
		copy[i] = ft_tolower(str[i]);
	return (copy);
}

void	cmp_builtin(char *name)
{
	char	*tmp;

	if (!name)
		return ;
	tmp = str_tolower(name);
	if (!ft_strcmp(tmp, "cd") || !ft_strcmp(tmp, "echo")
		|| !ft_strcmp(tmp, "pwd") || !ft_strcmp(tmp, "env")
		|| !ft_strcmp(tmp, "exit") || !ft_strcmp(tmp, "export")
		|| !ft_strcmp(tmp, "unset"))
		ft_strlcpy(name, tmp, ft_strlen(name) + 1);
	free(tmp);
}

void	tolower_builtin(t_cmd *cmd)
{
	if (!cmd->args)
		return ;
	while (cmd && cmd->args)
	{
		cmp_builtin(cmd->args[0]);
		cmd = cmd->next;
	}
}

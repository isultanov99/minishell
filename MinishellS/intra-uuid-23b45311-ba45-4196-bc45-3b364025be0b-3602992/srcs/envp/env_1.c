/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:19:38 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:19:38 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	создаёт односвязный список, состоящий
**	из переменных окружения
*/

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
	g_data.env = list;
}

/*
**	полностью очищает память односвязного списка
*/

void	env_free(t_list *list)
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

/*
**	выводит переменные окружения
*/

void	env_print(int fd)
{
	t_list	*cp;

	cp = g_data.env;
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

/*
**	возвращает элемент односвязного списка, в котором
**	содержится строка, которая предшествует строке, в
**	которой содержится переменная, которую нужно удалить
*/

static t_list	*env_get_pre_str(char *var, int var_size)
{
	t_list	*cp;

	cp = g_data.env;
	if (cp && ft_strncmp((char *)cp->content, var, var_size) == 0
		&& (((char*)cp->content)[var_size] == '='
		|| ((char*)cp->content)[var_size] == '\0'))
		return (NULL);
	while (cp)
	{
		if (cp->next
			&& ft_strncmp((char *)(cp->next)->content, var, var_size) == 0
			&& (((char*)(cp->next)->content)[var_size] == '='
			|| ((char*)(cp->next)->content)[var_size] == '\0'))
			break ;
		cp = cp->next;
	}
	return (cp);
}

/*
**	удаляет из списка элемент, в котором
**	содержится переменная, поданная на вход
**	возвращает 0 в случае успеха и 1 в ином случае
*/

int	env_delete_var(char *var)
{
	int		var_size;
	t_list	*str;
	t_list	*pre;

	var_size = ft_strlen(var);
	str = env_get_str(var, var_size);
	if (str == NULL)
		return (1);
	pre = env_get_pre_str(var, var_size);
	if (pre == NULL)
		g_data.env = str->next;
	else
		pre->next = str->next;
	free(str->content);
	free(str);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:19:20 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:19:20 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	сортирует переменные экспорта в
**	алфавитном порядке по возрастанию
*/

void	exp_sort(t_list *list)
{
	t_list	*i;
	t_list	*j;
	char	*buf;

	i = list;
	while (i)
	{
		j = list;
		while (j)
		{
			if (strcmp(i->content, j->content) < 0)
			{
				buf = i->content;
				i->content = j->content;
				j->content = buf;
			}
			j = j->next;
		}
		i = i->next;
	}
}

/*
**	создаёт односвязный список - дубликат,
**	состоящий из переменных окружения
*/

t_list	*env_dup(void)
{
	t_list	*begin_env;
	t_list	*dup_env;

	begin_env = g_data.env;
	dup_env = NULL;
	while (begin_env)
	{
		ft_lstadd_back(&dup_env, ft_lstnew(ft_strdup(begin_env->content)));
		begin_env = begin_env->next;
	}
	return (dup_env);
}

void	str_put(char *s, int fd)
{
	int		i;
	int		flag;

	if (s == NULL)
		return ;
	i = 0;
	flag = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		if (s[i] == '=' && flag == 0)
		{
			write(fd, "\"", 1);
			flag = 1;
		}
		i++;
	}
	if (flag == 1)
		write(fd, "\"", 1);
}

/*
**	выводит переменные окружения через export без аргументов
*/

void	export_print(int fd)
{
	t_list	*list;
	t_list	*mind;

	list = env_dup();
	mind = list;
	exp_sort(list);
	while (list)
	{
		ft_putstr_fd("declare -x ", fd);
		str_put((char *)list->content, fd);
		write(fd, "\n", 1);
		list = list->next;
	}
	env_free(mind);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:19:41 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:19:41 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	создаёт строку из переменной и
**	её значения через знак равно
*/

static char	*env_new_str(char *var, char *value)
{
	char	*new_str;
	char	*mind;

	if (value == NULL)
		return (ft_strdup(var));
	new_str = ft_strjoin(var, "=");
	mind = new_str;
	new_str = ft_strjoin(new_str, value);
	free(mind);
	return (new_str);
}

/*
**	добавляет новую переменную
*/

void	env_add_new_var(char *var, char *value)
{
	char	*new_str;

	new_str = env_new_str(var, value);
	ft_lstadd_back(&(g_data.env), ft_lstnew(new_str));
}

/*
**	изменяет значение переменной, которую принимает
**	первым аргументом
**	возвращает 0 в случае успеха и 1 в ином случае
*/

int	env_change_var(char *var, char *value)
{
	int		var_size;
	t_list	*list;
	char	*new_str;

	var_size = ft_strlen(var);
	list = env_get_str(var, var_size);
	if (list == NULL)
		return (1);
	if (value == NULL)
		return (0);
	new_str = env_new_str(var, value);
	free(list->content);
	list->content = new_str;
	return (0);
}

/*
**	возвращает элемент односвязного списка, в котором
**	содержится строка с нужной переменной
**	если такой строки нет, то будет возвращено NULL
*/

t_list	*env_get_str(char *var, int var_size)
{
	t_list	*cp;

	cp = g_data.env;
	while (cp)
	{
		if (ft_strncmp((char *)cp->content, var, var_size) == 0
			&& (((char*)cp->content)[var_size] == '='
			|| ((char *)cp->content)[var_size] == '\0'))
			break ;
		cp = cp->next;
	}
	if (cp == NULL)
		return (NULL);
	return (cp);
}

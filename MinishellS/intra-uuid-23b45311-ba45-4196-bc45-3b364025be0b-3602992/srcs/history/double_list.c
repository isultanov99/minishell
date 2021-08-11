/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:19:50 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:19:50 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dlist	*dlist_new(void *content)
{
	t_dlist	*new;

	new = (t_dlist *)malloc(sizeof(t_dlist));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	dlist_add_back(t_dlist **dlist, t_dlist *new)
{
	t_dlist	*begin;

	if (dlist == NULL || new == NULL)
		return ;
	if (*dlist == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*dlist = new;
		return ;
	}
	begin = *dlist;
	while (begin->next)
		begin = begin->next;
	begin->next = new;
	new->next = NULL;
	new->prev = begin;
}

void	dlist_print(t_dlist *dlist)
{
	t_dlist	*copy;

	copy = dlist;
	while (copy)
	{
		printf("%s", (char *)copy->content);
		copy = copy->next;
	}
}

void	dlist_free(t_dlist *dlist)
{
	t_dlist	*mind;

	while (dlist)
	{
		mind = dlist->next;
		free(dlist->content);
		free(dlist);
		dlist = mind;
	}
}

void	dlist_end(void)
{
	g_data.history.hist_end = g_data.history.hist_start;
	while (g_data.history.hist_end)
	{
		if (g_data.history.hist_end->next == NULL)
			break ;
		g_data.history.hist_end = g_data.history.hist_end->next;
	}
}

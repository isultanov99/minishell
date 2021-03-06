/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:10:17 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/17 19:10:19 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_dlist	*dlist_new(void *content)
{
	t_dlist	*new;

	new = (t_dlist *)malloc(sizeof(t_dlist));
	if (new == 0)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	dlist_add_back(t_dlist **dlist, t_dlist *new)
{
	t_dlist	*begin;

	if (dlist == 0 || new == 0)
		return ;
	if (*dlist == 0)
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

void	dlist_end(void)
{
	g_main.hist.h_end = g_main.hist.h_start;
	while (g_main.hist.h_end)
	{
		if (g_main.hist.h_end->next == 0)
			break ;
		g_main.hist.h_end = g_main.hist.h_end->next;
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

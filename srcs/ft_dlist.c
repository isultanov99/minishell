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
	g_main.history.hist_end = g_main.history.hist_start;
	while (g_main.history.hist_end)
	{
		if (g_main.history.hist_end->next == 0)
			break ;
		g_main.history.hist_end = g_main.history.hist_end->next;
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

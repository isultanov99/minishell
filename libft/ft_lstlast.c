/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 21:04:01 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/20 21:24:52 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*list;

	list = lst;
	if (list == NULL)
	{
		return (NULL);
	}
	else
	{
		while (list->next)
			list = list->next;
		return (list);
	}
}

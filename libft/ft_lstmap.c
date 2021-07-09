/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:15:06 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/23 14:49:48 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*b_lst;
	t_list	*b_elem;

	if (!lst)
		return (0);
	b_elem = ft_lstnew(f(lst->content));
	if (!(b_elem))
		return (0);
	b_lst = b_elem;
	lst = lst->next;
	while (lst)
	{
		b_elem = ft_lstnew(f(lst->content));
		if (!(b_elem))
		{
			ft_lstclear(&b_lst, del);
			return (0);
		}
		lst = lst->next;
		ft_lstadd_back(&b_lst, b_elem);
	}
	return (b_lst);
}

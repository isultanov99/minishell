/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:25:03 by lkarliah          #+#    #+#             */
/*   Updated: 2021/04/13 18:51:38 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*del_lst;

	del_lst = NULL;
	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		del_lst = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = del_lst;
	}
}

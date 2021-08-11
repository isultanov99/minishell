/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:53:12 by natali            #+#    #+#             */
/*   Updated: 2021/06/08 17:33:34 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *begin_list, void *data_ref,
	int (*cmp)())
{
	while (begin_list)
	{
		if (!cmp(data_ref, begin_list))
		{
			return (begin_list);
			break ;
		}
		else
			begin_list = begin_list->next;
	}
	return (NULL);
}

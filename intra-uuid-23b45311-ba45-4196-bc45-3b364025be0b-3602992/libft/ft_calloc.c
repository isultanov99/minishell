/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:48:04 by lkarliah          #+#    #+#             */
/*   Updated: 2021/04/17 18:51:15 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t size)
{
	void	*buf;

	buf = malloc(size);
	if (buf == NULL)
		return (NULL);
	ft_bzero(buf, size);
	return (buf);
}

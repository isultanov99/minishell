/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 23:44:17 by bmangree          #+#    #+#             */
/*   Updated: 2021/05/18 18:21:14 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			len;
	const char	ch = c;

	len = ft_strlen(s);
	s = s + len;
	while (*s != ch)
	{
		if (--len < 0)
			return (NULL);
		s--;
	}
	return ((char *)s);
}

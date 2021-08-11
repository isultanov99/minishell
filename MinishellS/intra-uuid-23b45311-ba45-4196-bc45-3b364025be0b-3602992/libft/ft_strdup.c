/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:04:28 by lkarliah          #+#    #+#             */
/*   Updated: 2021/07/22 12:53:45 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	while (*src != '\0')
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;

	if (s1)
	{
		copy = malloc(ft_strlen(s1) + 1);
		if (copy == NULL)
			return (NULL);
		ft_strcpy(copy, s1);
		return (copy);
	}
	return (NULL);
}

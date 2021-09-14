/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:54:26 by cpablo            #+#    #+#             */
/*   Updated: 2020/11/11 19:54:29 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;
	size_t		i;
	size_t		len;

	if (!s1 || !s2)
		return (NULL);
	dest = NULL;
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(dest = (char*)malloc(sizeof(*dest) * len)))
		return (NULL);
	while (*s1 != '\0')
		dest[i++] = *s1++;
	while (*s2 != '\0')
		dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
}

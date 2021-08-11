/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:11:26 by lkarliah          #+#    #+#             */
/*   Updated: 2021/07/26 17:05:48 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	sub_len;

	if (!s)
		return (NULL);
	if (start >= (size_t)ft_strlen(s))
	{
		sub = malloc(1);
		*sub = '\0';
		return (sub);
	}
	sub_len = ft_strlen(s) - start;
	if (sub_len < len)
		sub = malloc(sub_len + 1);
	else
		sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (len-- > 0 && s[start])
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 23:10:56 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/04 16:40:54 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char c, const char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	char	*copy;
	int		i;
	int		len;

	if (!s1 || !set)
		return (NULL);
	while (ft_check(*s1, set) == 1)
		s1++;
	if (!*s1)
	{
		copy = ft_calloc(1);
		return (copy);
	}
	i = 0;
	len = ft_strlen(s1) - 1;
	while (ft_check(s1[len--], set) == 1)
		i++;
	len = ft_strlen(s1) - i + 1;
	copy = malloc(len);
	i = 0;
	while (len-- > 1)
		copy[i++] = *s1++;
	copy[i] = '\0';
	return (copy);
}

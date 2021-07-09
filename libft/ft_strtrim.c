/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:58:58 by bmangree          #+#    #+#             */
/*   Updated: 2021/05/18 18:20:41 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(const char c, const char *set)
{
	while (*set != c)
	{
		if (*set == '\0')
			return (0);
		set++;
	}
	return (1);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*rets;
	int		i;
	int		len;

	if (s == NULL)
		return (NULL);
	while (ft_isinset(*s, set) && *s)
		s++;
	if (!*s)
	{
		rets = malloc(1);
		*rets = '\0';
		return (rets);
	}
	len = ft_strlen(s);
	while (ft_isinset(s[len - 1], set))
		len--;
	rets = malloc(len + 1);
	if (!(rets))
		return (NULL);
	i = 0;
	while (i != len)
		rets[i++] = *s++;
	rets[i] = '\0';
	return (rets);
}

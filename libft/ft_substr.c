/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:14:56 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/20 19:18:21 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	ss = malloc(len + 1);
	if (!(ss))
		return (NULL);
	i = 0;
	while (i != len)
		ss[i++] = s[start++];
	ss[i] = '\0';
	return (ss);
}

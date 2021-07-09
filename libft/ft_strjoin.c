/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 02:20:35 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/20 19:17:33 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	int		i;
	char	*s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	s = malloc(len + 1);
	if (!(s))
		return (NULL);
	while (*s1)
		s[i++] = *s1++;
	while (i != len || *s2)
		s[i++] = *s2++;
	s[i] = '\0';
	return (s);
}

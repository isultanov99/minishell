/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 19:09:40 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/20 19:40:12 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*fs;
	size_t	i;

	if (s == NULL)
		return (NULL);
	fs = malloc(ft_strlen(s) + 1);
	if (!(fs))
		return (NULL);
	i = 0;
	while (i != ft_strlen(s))
	{
		fs[i] = f(i, s[i]);
		i++;
	}
	fs[i] = '\0';
	return (fs);
}

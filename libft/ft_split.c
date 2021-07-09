/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:25:53 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/24 06:16:34 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(char const *s, char c)
{
	int			i;
	int			a_len;

	a_len = 0;
	i = 0;
	if (s[i] != c && s[i] != '\0')
		a_len++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			a_len++;
		i++;
	}
	return (a_len);
}

static char	**ft_free_memory(char **array, int a_len)
{
	while (a_len >= 0)
	{
		free(array[a_len]);
		a_len--;
	}
	free(array);
	return (NULL);
}

char	**processing(int a_len, char const *s, char c)
{
	char	**array;
	int		i;
	int		j;

	array = malloc(sizeof(char *) * (a_len + 1));
	if (!(array))
		return (NULL);
	j = 0;
	while (j < a_len)
	{
		i = 0;
		while (*s == c)
			s++;
		while (s[i] != c && s[i])
			i++;
		array[j] = ft_substr(s, 0, i);
		if (!(array[j]))
			return (ft_free_memory(array, a_len));
		s += i;
		j++;
	}
	array[a_len] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		a_len;

	if (!s)
		return (NULL);
	a_len = count_len(s, c);
	return (processing(a_len, s, c));
}

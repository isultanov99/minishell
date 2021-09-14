/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:54:39 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/14 14:24:59 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *str, char c)
{
	int	res;
	int	i;

	i = 0;
	res = 1;
	if (!str)
		return (0);
	if (c == '\0')
		return (res);
	while (str[i] && str[i] == c)
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1])
			res++;
		i++;
	}
	return (res);
}

static int	ft_count_len(char const *str, char c)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i] != c && str[i])
	{
		res++;
		i++;
	}
	return (res);
}

static void	*ft_free(char **array, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		if (array[i])
		{
			free(array[i]);
			array[i] = NULL;
		}
		i++;
	}
	if (array)
	{
		free(array);
		array = NULL;
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		words;
	int		num;

	if (!s)
		return (NULL);
	num = 0;
	words = ft_count_words(s, c);
	array = (char **)malloc((words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (num < words)
	{
		while (*s == c && *s)
			s++;
		array[num] = ft_substr(s, 0, ft_count_len(s, c));
		if (!array[num])
			return (ft_free(array, words));
		while (*s != c && *s)
			s++;
		num++;
	}
	array[words] = NULL;
	return (array);
}

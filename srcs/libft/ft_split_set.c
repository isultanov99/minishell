/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:33:32 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/14 14:33:32 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_chr(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int	check_str_set(char *str, char *set)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (!str || !*str)
		return (1);
	while (*str)
	{
		if (check_chr(*str, set))
			i++;
		str++;
	}
	if (i == len)
		return (1);
	return (0);
}

static int	count_words(char *str, char *set)
{
	int	count;

	count = 1;
	if (check_str_set(str, set))
		return (0);
	while (check_chr(*str, set))
		str++;
	while (*(str + 1))
	{
		if (check_chr(*str, set) && !(check_chr(*(str + 1), set)))
			count++;
		str++;
	}
	return (count);
}

static int	count_len(char *str, char *set)
{
	int	len;

	len = 0;
	while (*str && !(check_chr(*str, set)))
	{
		str++;
		len++;
	}
	return (len);
}

char	**ft_split_set(char *str, char *set)
{
	char	**splitted;
	int		words;
	int		i;

	if (!str || !set)
		return (NULL);
	words = count_words(str, set);
	i = 0;
	splitted = (char **)malloc((words + 1) * sizeof(char *));
	if (!splitted)
		return (NULL);
	while (i < words)
	{
		while (check_chr(*str, set))
			str++;
		splitted[i] = ft_substr(str, 0, count_len(str, set));
		if (!splitted[i])
			return (array_free((void **)splitted));
		str += count_len(str, set);
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}

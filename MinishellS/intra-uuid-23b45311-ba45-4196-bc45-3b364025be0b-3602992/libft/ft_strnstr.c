/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:29:23 by lkarliah          #+#    #+#             */
/*   Updated: 2021/07/26 17:04:52 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!haystack || !needle)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (i < len && *haystack)
	{
		if (*haystack == *needle && len - i >= (size_t)ft_strlen(needle)
			&& !(ft_strncmp(haystack, needle, ft_strlen(needle))))
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}

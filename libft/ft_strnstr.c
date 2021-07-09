/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:12:59 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/19 00:40:07 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t s_len)
{
	size_t	ss_len;

	ss_len = ft_strlen(substr);
	while (ft_strncmp(str, substr, ss_len) != 0)
	{
		if (*str++ == '\0' || s_len == 0 || --s_len < ss_len)
			return (NULL);
	}
	return ((char *)str);
}

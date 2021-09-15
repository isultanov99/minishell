/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:53:48 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/15 19:38:26 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	sublen;

	if (!str || str == 0)
		return (NULL);
	if ((size_t)ft_strlen(str) < start)
		return (ft_strdup(""));
	sublen = ft_strlen(str + start);
	if (sublen < len)
		len = sublen;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, str + start, len + 1);
	return (substr);
}

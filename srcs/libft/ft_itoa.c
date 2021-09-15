/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:56:13 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/15 19:47:11 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_value(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

static int	ft_get_len(int num)
{
	int	len;

	len = 0;
	if (num <= 0)
		len++;
	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		len;

	len = ft_get_len(n);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	if (n < 0)
		dest[0] = '-';
	else if (n == 0)
		dest[0] = '0';
	while (n != 0)
	{
		len--;
		dest[len] = ft_get_value(n % 10) + '0';
		n /= 10;
	}
	return (dest);
}

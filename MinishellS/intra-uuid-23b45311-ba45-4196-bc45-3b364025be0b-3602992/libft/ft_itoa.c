/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:19:12 by lkarliah          #+#    #+#             */
/*   Updated: 2021/04/13 18:31:22 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lenth(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		len = 11;
	else if (n < 0)
	{
		len += 1;
		n *= (-1);
	}
	if (n == 0)
		len = 1;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len - 1);
}

char	*ft_itoa(int n)
{
	char	*numb;
	int		len;

	len = ft_lenth(n);
	numb = malloc(len + 2);
	numb[len + 1] = '\0';
	if (n == -2147483648)
	{
		n /= 10;
		numb[len--] = '8';
	}
	if (n < 0)
	{
		numb[0] = '-';
		n *= (-1);
	}
	if (n == 0)
		numb[0] = '0';
	while (n > 0)
	{
		numb[len--] = n % 10 + '0';
		n /= 10;
	}
	return (numb);
}

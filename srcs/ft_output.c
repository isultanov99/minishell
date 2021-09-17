/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:10:30 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/17 19:10:31 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	arr_size(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	print_msg(void)
{
	char	*message;
	char	**spt_strs;
	int		i;

	message = getcwd(NULL, 0);
	if (message[0] == '/' && message[1] == '\0')
	{
		home_dir(message);
		return ;
	}
	spt_strs = ft_split(message, '/');
	free(message);
	ft_putstr_fd("\033[1;36m", 1);
	ft_putstr_fd(spt_strs[arr_size(spt_strs) - 1], 1);
	write(1, ": ", 2);
	ft_putstr_fd("\033[0m", 1);
	tputs(tgetstr("sc", 0), 1, output_func);
	i = 0;
	while (spt_strs[i])
	{
		free(spt_strs[i]);
		i++;
	}
	free(spt_strs);
}

int	output_func(int c)
{
	return (write(1, &c, 1));
}

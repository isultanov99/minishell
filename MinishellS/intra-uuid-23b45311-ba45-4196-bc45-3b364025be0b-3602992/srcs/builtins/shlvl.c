/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:19:33 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:19:33 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	проверяет на валидность уровень
**	он должен быть только цифровой
**	succes = 0, fail = 1
*/

int	shlvl_valid(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}

/*
**	увеличивает на один уровень значение SHLVL
*/

void	shlvl_increment(char *shlvl)
{
	int		lvl;
	char	*new_shlvl;

	lvl = ft_atoi(shlvl);
	lvl += 1;
	new_shlvl = ft_itoa(lvl);
	env_change_var("SHLVL", new_shlvl);
	free(new_shlvl);
}

void	shlvl_set(void)
{
	char	*shlvl;
	int		is_changed;

	shlvl = env_get_var("SHLVL");
	if (shlvl == NULL)
	{
		is_changed = env_change_var("SHLVL", "1");
		if (is_changed == 1)
			env_add_new_var("SHLVL", "1");
		return ;
	}
	if (shlvl_valid(shlvl) == 1)
		env_change_var("SHLVL", "1");
	else
		shlvl_increment(shlvl);
	free(shlvl);
}

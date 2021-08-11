/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:20:14 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:20:14 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	output_func(int c)
{
	int				i;

	i = write(1, &c, 1);
	return (i);
}

/*
**	1) get term struct
**	2) change this struct
**	3) save changes
**	4) apply this changes
*/

void	setup_term(void)
{
	struct termios	setup;
	char			*term;

	tcgetattr(0, &setup);
	setup.c_lflag &= (~ECHO);
	setup.c_lflag &= (~ICANON);
	tcsetattr(0, 0, &setup);
	tgetent(0, term = env_get_var("TERM"));
	free(term);
}

void	reset_term(void)
{
	char			*term;

	tcsetattr(0, 0, &g_data.termset);
	tgetent(0, term = env_get_var("TERM"));
	free(term);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:44:09 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/15 20:44:23 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	tcsetattr(0, 0, &g_main.termset);
	tgetent(0, term = env_get_var("TERM"));
	free(term);
}
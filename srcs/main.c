/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:09:56 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/17 19:09:59 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	g_main.sig_pid = 0;
	g_main.status = 0;
	(void)argv;
	(void)argc;
	set_signal();
	tcgetattr(0, &g_main.termset);
	set_term();
	tputs(tgetstr("cl", 0), 1, output_func);
	env_get(envp);
	set_shlvl();
	h_create();
	input();
	dlist_free(g_main.hist.h_start);
	close(g_main.hist.h_fd);
	list_free(g_main.env);
}

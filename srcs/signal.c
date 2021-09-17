/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:15:10 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/17 18:57:03 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_int(int code)
{
	(void)code;
	write(1, "\n", 1);
	if (g_main.sig_pid == 0)
	{
		print_msg();
		g_main.status = 1;
		if (g_main.hist.flag == 1)
			h_inp();
		main_inp();
	}
	if (g_main.sig_pid > 0)
		g_main.status = 130;
}

void	sig_quit(int code)
{
	(void)code;
	if (g_main.sig_pid != 0)
	{
		if (ft_strcmp(g_main.hist.command, "read") != 0)
		{
			write(1, "Quit: ", 6);
			ft_putnbr_fd(code, 1);
			write(1, "\n", 1);
		}
		g_main.status = 131;
	}
}

void	set_sig(void)
{
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int);
}

void	sigint_handler(int code)
{
	pid_t	id;

	(void)code;
	ft_putstr_fd("\n", 1);
	id = getpid();
	kill(id, SIGKILL);
}

void	sigquit_handler(int code)
{
	(void)code;
}

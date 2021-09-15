/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <bmangree@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:25:00 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/15 22:30:09 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_input(void)
{
	g_main.history.command = str_end(g_main.history.command);
	if (g_main.history.command[0] != '\0')
	{
		hist_add_str(g_main.history.command);
		parse_cmd(g_main.history.command);
	}
	g_main.history.command_print = 0;
	dlist_end();
}

void	hist_input(void)
{
	g_main.history.hist_end->content
		= str_end(g_main.history.hist_end->content);
	if (((char *)(g_main.history.hist_end->content))[0] != '\0')
	{
		hist_add_str(g_main.history.hist_end->content);
		parse_cmd(g_main.history.hist_end->content);
	}
	free(g_main.history.hist_end->content);
	g_main.history.hist_end->content = ft_strdup(g_main.history.hist_buf);
	dlist_end();
}

void	main_inp(void)
{
	g_main.history.flag = 0;
	if (g_main.history.command != NULL)
		free(g_main.history.command);
	g_main.history.command = NULL;
	g_main.history.command_print = 0;
	dlist_end();
}

void	hist_inp(void)
{
	free(g_main.history.hist_end->content);
	g_main.history.hist_end->content = ft_strdup(g_main.history.hist_buf);
}

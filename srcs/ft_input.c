/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:25:00 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/17 18:03:13 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_input(void)
{
	g_main.hist.command = str_end(g_main.hist.command);
	if (g_main.hist.command[0] != '\0')
	{
		h_add_str(g_main.hist.command);
		parse_cmd(g_main.hist.command);
	}
	g_main.hist.command_print = 0;
	dlist_end();
}

void	h_input(void)
{
	g_main.hist.h_end->content
		= str_end(g_main.hist.h_end->content);
	if (((char *)(g_main.hist.h_end->content))[0] != '\0')
	{
		h_add_str(g_main.hist.h_end->content);
		parse_cmd(g_main.hist.h_end->content);
	}
	free(g_main.hist.h_end->content);
	g_main.hist.h_end->content = ft_strdup(g_main.hist.h_buf);
	dlist_end();
}

void	main_inp(void)
{
	g_main.hist.flag = 0;
	if (g_main.hist.command != NULL)
		free(g_main.hist.command);
	g_main.hist.command = NULL;
	g_main.hist.command_print = 0;
	dlist_end();
}

void	h_inp(void)
{
	free(g_main.hist.h_end->content);
	g_main.hist.h_end->content = ft_strdup(g_main.hist.h_buf);
}

void	input(void)
{
	int		i;
	char	buf[4];

	print_message();
	g_main.hist.command_print = 0;
	g_main.hist.command = NULL;
	g_main.hist.h_buf = NULL;
	while (1)
	{
		i = read(0, buf, 3);
		buf[i] = '\0';
		if (!keys(buf) && n_is_print(buf) == 0)
		{
			write(1, buf, i);
			h_or_command(buf);
		}
		control_characters(buf);
	}
	free(g_main.hist.command);
	free(g_main.hist.h_buf);
}

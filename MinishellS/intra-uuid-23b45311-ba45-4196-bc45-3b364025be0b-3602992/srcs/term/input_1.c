/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:19:59 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:19:59 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	проверяет строку на печатаемые символы
**	в данном контексте '\n' является печатаемым
*/

int	n_is_print(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) == 0 && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
**	отсекает от строки последний символ и возвращает новую строку
**	если отсечь нечего, то возвращается пустая строка
*/

char	*str_end(char *str)
{
	char	*new_str;
	int		str_size;
	int		i;

	if (str == NULL)
		return (ft_strdup(""));
	str_size = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * str_size);
	i = 0;
	while (str[i + 1] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

/*
**	соединяет две строки в одну команду
**	в случае неудачи, возвращает пустую строку
*/

char	*get_command(char *str, char *add)
{
	char	*command;

	command = ft_strjoin(str, add);
	if (command == NULL)
		command = ft_strdup(add);
	else
		free(str);
	free(add);
	return (command);
}

/*
**	дополняет команду, которая содержится
**	в истории, либо в основном вводе
*/

void	hist_or_command(char *buf)
{
	if (g_data.history.flag == 0)
	{
		g_data.history.command_print++;
		g_data.history.command
			= get_command(g_data.history.command, ft_strdup(buf));
	}
	if (g_data.history.flag == 1)
	{
		g_data.history.hist_print++;
		g_data.history.hist_end->content
			= get_command(g_data.history.hist_end->content, ft_strdup(buf));
	}
}

/*
**	главная функция ввода данных
*/

void	input(void)
{
	int		i;
	char	buf[4];

	print_message();
	g_data.history.command_print = 0;
	g_data.history.command = NULL;
	g_data.history.hist_buf = NULL;
	while (1)
	{
		i = read(0, buf, 3);
		buf[i] = '\0';
		if (!keys(buf) && n_is_print(buf) == 0)
		{
			write(1, buf, i);
			hist_or_command(buf);
		}
		control_characters(buf);
	}
	free(g_data.history.command);
	free(g_data.history.hist_buf);
}

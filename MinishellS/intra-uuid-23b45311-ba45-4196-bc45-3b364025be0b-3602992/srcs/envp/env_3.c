/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:19:44 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:19:44 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_get_var_mem_fill(char *ret_str, char *var_str, int var_size)
{
	int		i;

	i = 0;
	while (var_str[var_size + 1] != '\0')
	{
		ret_str[i] = var_str[var_size + 1];
		var_size++;
		i++;
	}
	ret_str[i] = '\0';
}

/*
**	возвращает значение переменной, которую принимает
**	первым аргументом
*/

char	*env_get_var(char *var)
{
	int		var_size;
	t_list	*list;
	char	*var_str;
	int		i;
	char	*ret_str;

	var_size = ft_strlen(var);
	list = env_get_str(var, var_size);
	if (list == NULL)
		return (NULL);
	var_str = list->content;
	i = 0;
	while (var_str[var_size + 1] != '\0')
	{
		var_size++;
		i++;
	}
	ret_str = (char *)malloc(sizeof(char) * (i + 1));
	var_size = ft_strlen(var);
	env_get_var_mem_fill(ret_str, var_str, var_size);
	return (ret_str);
}

/*
**	создаёт отдельный двумерный массив из односвязного списка env
*/

char	**ft_envp_arr(void)
{
	t_list	*envp_list;
	char	**envp_arr;
	int		i;

	envp_list = g_data.env;
	envp_arr = (char **)malloc(sizeof(char *) * (ft_lstsize(envp_list) + 1));
	i = 0;
	while (envp_list)
	{
		envp_arr[i] = ft_strdup(envp_list->content);
		i++;
		envp_list = envp_list->next;
	}
	envp_arr[i] = NULL;
	return (envp_arr);
}

void	ft_envp_arr_free(char **envp_arr)
{
	int		i;

	i = 0;
	while (envp_arr[i])
	{
		free(envp_arr[i]);
		i++;
	}
	free(envp_arr);
}

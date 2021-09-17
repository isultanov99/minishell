#include "../includes/minishell.h"

t_list	*env_get_str(char *var, int var_size)
{
	t_list	*cp;

	cp = g_main.env;
	while (cp)
	{
		if (ft_strncmp((char *)cp->content, var, var_size) == 0
			&& (((char*)cp->content)[var_size] == '='
			|| ((char *)cp->content)[var_size] == '\0'))
			break ;
		cp = cp->next;
	}
	if (cp == 0)
		return (NULL);
	return (cp);
}

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

char	*env_get_var(char *var)
{
	int		var_size;
	t_list	*list;
	char	*var_str;
	int		i;
	char	*ret_str;

	var_size = ft_strlen(var);
	list = env_get_str(var, var_size);
	if (list == 0)
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

char	**envp_arr(void)
{
	t_list	*envp_list;
	char	**envp_arr;
	int		i;

	envp_list = g_main.env;
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

void	envp_arr_free(char **envp_arr)
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

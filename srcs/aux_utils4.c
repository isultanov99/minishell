#include "../includes/minishell.h"

void	export_value_mem_fill(char *value, char *str, int i)
{
	int		k;

	k = 0;
	while (str[i])
	{
		value[k] = str[i];
		k++;
		i++;
	}
	value[k] = '\0';
}

char	*export_value(char *str)
{
	char	*value;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	j = i;
	k = 0;
	while (str[i])
	{
		i++;
		k++;
	}
	value = (char *)malloc(sizeof(char) * (k + 1));
	i = j;
	export_value_mem_fill(value, str, i);
	return (value);
}

int	export_add(int fd, char *str)
{
	char	*var;
	char	*value;
	int		is_changed;

	var = export_var(str);
	if (var_valid(var) == 1)
	{
		var_print_error(fd, var);
		free(var);
		return (1);
	}
	value = export_value(str);
	is_changed = change_env_var(var, value);
	if (is_changed)
		env_add_new_var(var, value);
	free(var);
	free(value);
	return (0);
}

int	ft_datalen(t_data *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_data	*last_data(t_data *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

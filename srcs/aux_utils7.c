#include "../includes/minishell.h"

static t_list	*env_get_pre_str(char *var, int var_size)
{
	t_list	*cp;

	cp = g_main.env;
	if (cp && ft_strncmp((char *)cp->content, var, var_size) == 0
		&& (((char*)cp->content)[var_size] == '='
		|| ((char*)cp->content)[var_size] == '\0'))
		return (NULL);
	while (cp)
	{
		if (cp->next
			&& ft_strncmp((char *)(cp->next)->content, var, var_size) == 0
			&& (((char*)(cp->next)->content)[var_size] == '='
			|| ((char*)(cp->next)->content)[var_size] == '\0'))
			break ;
		cp = cp->next;
	}
	return (cp);
}

int	env_delete_var(char *var)
{
	int		var_size;
	t_list	*str;
	t_list	*pre;

	var_size = ft_strlen(var);
	str = env_get_str(var, var_size);
	if (str == 0)
		return (1);
	pre = env_get_pre_str(var, var_size);
	if (pre == 0)
		g_main.env = str->next;
	else
		pre->next = str->next;
	free(str->content);
	free(str);
	return (0);
}

static char	*env_new_str(char *var, char *value)
{
	char	*new_str;
	char	*mind;

	if (value == 0)
		return (ft_strdup(var));
	new_str = ft_strjoin(var, "=");
	mind = new_str;
	new_str = ft_strjoin(new_str, value);
	free(mind);
	return (new_str);
}

void	env_add_new_var(char *var, char *value)
{
	char	*new_str;

	new_str = env_new_str(var, value);
	ft_lstadd_back(&(g_main.env), ft_lstnew(new_str));
}

int	env_change_var(char *var, char *value)
{
	int		var_size;
	t_list	*list;
	char	*new_str;

	var_size = ft_strlen(var);
	list = env_get_str(var, var_size);
	if (list == 0)
		return (1);
	if (value == 0)
		return (0);
	new_str = env_new_str(var, value);
	free(list->content);
	list->content = new_str;
	return (0);
}

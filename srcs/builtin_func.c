#include "../includes/minishell.h"

void	pwd(void)
{
	char *pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	pwd = NULL;
}

void	cd(const char *cd)
{
	chdir(cd);
}

void	echo(char **line)
{
	int i;

	i = 1;
	while (line[i] != NULL)
	{
		printf("%s", line[i]);
		i++;
	}
	printf("\n");
}

char			**count_commands(char *line)
{
	int		i;
	int		count;
	char	**command_line;
	int		flag;

	command_line = NULL;
	count = 0;
	flag = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
		{
			count = count + 1;
			while ((line[i] != ' ' || flag == 1 || flag == 2) && line[i] != '\0')
			{
				if (line[i] == '"' || line[i] == '\'')
				{
					if (flag == 0 && line[i] == '"')
						flag = 1;
					else if (flag == 1 && line[i] == '"')
						flag = 0;
					else if (flag == 0 && line[i] == '\'')
						flag = 2;
					else if (flag == 2 && line[i] == '\'')
						flag = 0;
				}
				i = i + 1;
			}
		}
		else
			i = i + 1;
	}
	command_line = malloc(sizeof(char *) * (count + 1));
	return (command_line);
}

int main(int argc, char **argv)
{
	char **command_line;

	command_line = malloc(sizeof(char *) * 100);
	command_line[0] = "авыаыа";
	cd("/Users/arsenyburov/Coding/");
	pwd();
	echo(&command_line[0]);
	return (0);
}
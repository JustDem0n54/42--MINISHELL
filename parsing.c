#include "minishell.h"

char	*ft_seperate(int start, int end, char *str)
{
	char	*new;
	int i;

	new = malloc(sizeof(char) * (end - start + 1));
	i = 0;
	while (start < end)
	{
		new[i] = str[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return(new);
}

int	check_token(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		return (2);
	else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (1);
	return (0);
}

t_list	*parsing_line(char *str)
{
	int i;
	int j;
	t_list *line;
	char *temp;

	i = 0;
	j = 0;
	line = NULL;
	while (str[i])
	{
		if (str[i] == ' ' && str[i - 1] != ' ')
		{
			temp = ft_seperate(j, i, str);
			ft_lstadd_back(&line, ft_lstnew(temp));
			i++;
			j = i;
		}
		else if (str[i + 1] == '\0')
		{
			temp = ft_seperate(j, i + 1, str);
			ft_lstadd_back(&line, ft_lstnew(temp));
			i++;
			j = i;
		}
		else if (check_token(str, i) == 1)
		{
			temp = ft_seperate(j, i, str);
			ft_lstadd_back(&line, ft_lstnew(temp));
			ft_lstadd_back(&line, ft_lstnew("|"));
			i++;
			j = i;
		}
		else if (check_token(str, i) == 2)
		{
			temp = ft_seperate(j, i, str);
			ft_lstadd_back(&line, ft_lstnew(temp));
			j = i;
			i++;
		}
		i++;
	}
	return (line);
}

char	*check_path(char **env, char *cmd)
{
	int		i;
	char	**path;
	char	*temp;

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
	}
	i = 0;
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	path = ft_split(env[i] + 5, ':');
	i = 0;
	while (path[i] != NULL)
	{
		temp = ft_strnjoin(2, (char *[]){path[i], cmd}, "/");
		if (access(temp, F_OK) == 0)
			return (free_split(path), temp);
		free(temp);
		i++;
	}
	return (free_split(path), NULL);
}


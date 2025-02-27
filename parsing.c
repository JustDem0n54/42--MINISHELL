#include "minishell.h"

int gest_quote(char *str, int i, int j, t_list **line)
{
	char	quote;
	char	*temp;
	
	quote = str[i];
	i++;
	while (str[i] != quote && str[i])
		i++;
	while (str[i+1] != ' ' && ft_strchr("<>|\"\'", str[i+1]) == NULL && str[i])
		i++;
	temp = ft_substr(str, j, i - j + 1);
	ft_lstadd_back(line, ft_lstnew(temp));
	i++;
	return (i);
}

int gest_token(char *str, int i, int j, t_list **line)
{
	char	*temp;

	if (str[i - 1] != ' ' && str[i - 1] != str[i] && i > 0
		&& ft_strchr("\"\'", str[i - 1]) == NULL)
	{
		temp = ft_substr(str, j, i - j);
		ft_lstadd_back(line, ft_lstnew(temp));
		j = i;
	}
	if (ft_strchr("<>", str[i + 1]) && ft_strchr("<>", str[i]))
		i++;
	temp = ft_substr(str, j, i - j + 1);
	ft_lstadd_back(line, ft_lstnew(temp));
	i++;
	return (i);
}

t_list	*parsing_line(char *str)
{
	int		i;
	int		j;
	t_list	*line;
	char	*temp;

	i = 0;
	j = 0;
	line = NULL;
	while (str[i])
	{
		while (str[i] == ' ' && str[i])
			i++;
		j = i;
		while (ft_strchr("<>|\'\" 	", str[i]) == NULL && str[i])
			i++;
		if (str[i] == ' ' || (str[i] == 0 && str[i - 1] != ' '))
		{
			temp = ft_substr(str, j, i - j);
			ft_lstadd_back(&line, ft_lstnew(temp));
			i++;
		}
		else if (str[i] && ft_strchr("\'\"", str[i]))
			i = gest_quote(str, i, j, &line);
		else if (str[i] && ft_strchr("<|>", str[i]))
			i = gest_token(str, i, j, &line);
		j = i;
	}
	return (line);
}

char	*check_cmd(char **env, char *cmd)
{
	int		i;
	char	**path;
	char	*temp;
	
	/*check builtins*/
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


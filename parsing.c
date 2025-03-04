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

char	*check_export(char *str, int size)
{
	char	*test;

	test = ft_strdup("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	if (str[size])
		size++;
	return (test);
}

char	*check_dollars(char *str, int i, int y)
{
	char	*temp;
	char	*cpy;
	int 	start;
	int j = 0;

	cpy = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] < '9' && str[i] >= '0')
				i++;
			else if ((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
			{
				start = i;
				while (((str[i] >= 'a' && str[i] <= 'z') || (str[i] < '9' && str[i] >= '0')
					|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_') && str[i])
					i++;
				temp = check_export(str + start, i - start);
				while (temp[j])
					cpy[y++] = temp[j++];
			}
		}
		cpy[y++] = str[i++];
	}
	cpy[y] = 0;
	return (cpy);
}

char	*check_quote(char *str, int i, int y)
{
	char quote;
	char *cpy;

	cpy = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (ft_strchr("\'\"", str[i]) != NULL && str[i])
		{
			quote = str[i];
			i++;
			while (str[i] != quote && str[i])
				cpy[y++] = str[i++];
			i++;
		}
		cpy[y++] = str[i++];
	}
	cpy[y] = 0;
	return (cpy);
}

char	**convert_parse(t_list *lst)
{
	char *temp;
	char **sortie;
	int i;

	i = 0;
	sortie = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	while (lst)
	{
		temp = lst->content;
		temp = check_dollars(temp, 0, 0);
		sortie[i] = check_quote(temp, 0, 0);
		i++;
		lst = lst->next;
	}
	sortie[i] = NULL;
	return(sortie);
}

// char	*check_cmd(char **env, char *cmd)
// {
// 	int		i;
// 	char	**path;
// 	char	*temp;
	
// 	/*check builtins*/
// 	if (ft_strchr(cmd, '/') != NULL)
// 	{
// 		if (access(cmd, F_OK) == 0)
// 			return (cmd);
// 	}
// 	i = 0;
// 	while (ft_strncmp(env[i], "PATH", 4) != 0)
// 		i++;
// 	path = ft_split(env[i] + 5, ':');
// 	i = 0;
// 	while (path[i] != NULL)
// 	{
// 		temp = ft_strnjoin(2, (char *[]){path[i], cmd}, "/");
// 		if (access(temp, F_OK) == 0)
// 			return (free_split(path), temp);
// 		free(temp);
// 		i++;
// 	}
// 	return (free_split(path), NULL);
// }


#include "minishell.h"

int	gest_quote(char *str, int i, int j, t_list **line)
{
	char	quote;
	char	*temp;
	
	quote = str[i];
	i++;
	while (str[i] != quote && str[i])
		i++;
	while (str[i + 1] != ' ' && ft_strchr("<>|", str[i + 1]) == NULL && str[i])
		i++;
	temp = ft_substr(str, j, i - j + 1);
	ft_lstadd_back(line, ft_lstnew(temp));
	i++;
	return (i);
}

int	gest_token(char *str, int i, int j, t_list **line)
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
	// print_lst(line);
	printf("%s$\n", str);
	printf("0 =%d$\n", i);
	while (str[i])
	{
		// printf("1 =%c$\n", str[i]);
		while (str[i] == ' ' && str[i])
		{
			i++;
			// printf("2 =%c$\n", str[i]);
		}
		j = i;
		printf("1 =%d$\n", i);
		// printf("0 =%d$\n", str);
		while (str[i] && ft_strchr("<>|\'\" 	", str[i]) == NULL)
		{
			i++;
			// printf("3 =%c$\n", str[i]);
		}
		// printf("4 before =%c$\n", str[i + 1]);
		if (str[i] == ' ' || (str[i] == 0 && str[i - 1] != ' '))
		{
			temp = ft_substr(str, j, i - j);
			ft_lstadd_back(&line, ft_lstnew(temp));
			i++;
			printf("2 =%d$\n", i);
		}
		else if (str[i] && ft_strchr("\'\"", str[i]))
		{
			i = gest_quote(str, i, j, &line);
			// printf("5 =%c$\n", str[i]);
		}
		else if (str[i] && ft_strchr("<|>", str[i]))
			i = gest_token(str, i, j, &line);
		// printf("6 =%c$\n", str[i]);
		j = i;
		printf("3 =%d$\n", i);
	}
	// print_lst(line);
	return (line);
}

char	*check_export(char *str, int size)
{
	char	*test;

	test = ft_strdup("4");
	if (str[size])
		size++;
	return (test);
}

int	check_simple_quoke(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] == '$')
		{
			quote = str[i];
			i++;
			while (str[i] != quote && str[i])
				i++;
		}
		if (str[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

char	*check_dollars(char *str, int i, int y)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	*cpy;

	cpy = NULL;
	temp = NULL;
	temp2 = NULL;
	temp3 = NULL;
	while(str[i] != '$' && str[i])
		i++;
	if (str[i] == 0 || check_simple_quoke(str) == 0)
		return (str);
	if (str[i] == '$')
	{
		if (i > 0)
			temp = ft_substr(str, y, i - y);
		if (ft_isdigit(str[i + 1]) == 1)
		{
			i += 2;
			cpy = temp;
		}
		else if (ft_isalpha(str[i + 1]) == 1 || str[i + 1] == '_')
		{
			i++;
			y = i;
			while (ft_isalnum(str[i]) == 1 || str[i] == '_')
				i++;
			temp2 = check_export(str + y, i - y);
			if (temp2 == NULL)
				cpy = temp;
			else if (temp != NULL)
				cpy = ft_strnjoin(2, (char *[]){temp, temp2}, "");
			else
				cpy = temp2;
		}
		if (str[i] != 0 && str[i + 1] != 0)
		{
			y = i;
			while (str[i])
				i++;
			temp3 = ft_substr(str, y, i - y);
			cpy = ft_strnjoin(2, (char *[]){cpy, temp3}, "");
		}
	}
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
		else
			cpy[y++] = str[i++];
	}
	cpy[y] = 0;
	if (cpy[0] == 0)
		return (NULL);
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
		if (temp != NULL)
			temp = check_quote(temp, 0, 0);
		sortie[i] = temp;
		if (sortie[i] == NULL)
		{
			sortie[i] =	ft_strdup("");
			free(temp);
		}
		i++;
		lst = lst->next;
	}
	sortie[i] = 0;
	return(sortie);
}



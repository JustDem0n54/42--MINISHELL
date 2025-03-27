#include "../../minishell.h"

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

	if (i > 0 && str[i - 1] != ' ' && str[i - 1] != str[i]
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
	while (i < (int)ft_strlen(str) && str[i])
	{
		while (i < (int)ft_strlen(str) && str[i] == ' ' && str[i])
			i++;
		j = i;
		while (i < (int)ft_strlen(str) && str[i] && ft_strchr("<>|\'\" 	", str[i]) == NULL)
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

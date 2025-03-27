#include "../../minishell.h"

void	ft_ctrl_d_heredoc(t_var *var, char *eof)
{
	char	*nb_line;

	nb_line = ft_itoa(var->count_line);
	ft_putstr_fd("warning: here-document delimited at line ", 2);
	ft_putstr_fd(nb_line, 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(eof, 1);
	ft_putstr_fd("')\n", 2);
	free (nb_line);
}

void pos_end_dollar_var(char *str, int *i)
{

	// printf("i pos =%d\n", *i);
	*i = *i + 1;
	while (ft_isalnum(str[*i]) == 1 || str[*i] == '_')
		*i = *i + 1;
}

char	*dollar_value(t_var *var, char *str, int i, int y)
{
	char	*temp2;
	
	temp2 = NULL;
	temp2 = check_export(var, str + y, i - y);
	return (temp2);
}

char	*join_str_dollar_value(char *temp, char *temp2, char *cpy)
{
	if (temp2 == NULL)
		cpy = temp;
	else if (temp != NULL)
	{
		cpy = ft_strnjoin(2, (char *[]){temp, temp2}, "");
		free(temp);
		free(temp2);
	}
	else
		cpy = temp2;
	return (cpy);
}

char	*check_return_value(t_var *var, char *temp)
{
	char	*cpy;

	cpy = NULL;
	cpy = ft_itoa(var->status);
	if (temp != NULL)
		cpy = ft_strjoin(temp, cpy);
	return(cpy);
}

char	*parse_dollar(t_var *var, char *str, int *i, int y)
{
	char	*temp;
	char	*cpy;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	cpy = NULL;
	if (*i > 0)
		temp = ft_substr(str, y, *i - y);
	if (ft_isdigit(str[*i + 1]) == 1 || str[*i + 1] == '?')
	{
		if (ft_isdigit(str[*i + 1]) == 1)
			cpy = temp;
		else if (str[*i + 1] == '?')
			cpy = check_return_value(var, temp);
		*i += 2;
	}
	else if (ft_isalpha(str[*i + 1]) == 1 || str[*i + 1] == '_')
	{
		y = *i + 1;
		// printf("%d\n", *i);
		pos_end_dollar_var(str, i);
		// printf("%d\n", *i);
		temp2 = dollar_value(var, str, *i, y);
		// printf("%s\n", temp2);
		cpy = join_str_dollar_value(temp, temp2, cpy);
	}
	return (cpy);
}

char	*return_str(char *str, char *cpy, int i, int y)
{
	char	*temp3;
	char	*temp4;

	temp3 = NULL;
	temp4 = NULL;
	temp3 = ft_substr(str, y, i - y);
	temp4 = cpy;
	cpy = ft_strjoin(temp4, temp3);
	if (temp3)
		free(temp3);
	if (temp4)
		free(temp4);
	return (cpy);
}

char	*check_dollars_heredoc(t_var *var, char *str, int *i, int y)
{
	char	*cpy;

	cpy = NULL;
	while(str[*i] && str[*i] != '$' && *i < (int)ft_strlen(str) && str[*i])
		*i = *i + 1;
	// printf("%d\n", *i);
	if (str[*i] == '$')
	{
		cpy = parse_dollar(var, str, i, y);
		// if (str[*i] && ft_isalnum(str[*i]) == 0)
		// 	*i = *i + 1;
		y = *i;
		cpy = return_str(str, cpy, *i, y);	
	}
	else
	{
		cpy = ft_strdup(str);
		free(str);
	}
	// printf("iii =%d\n", *i);
	return(cpy);
}

char	*parse_all_str_heredoc(t_var *var, char *str, int i, int y)
{
	char	*temp;
	char	*newstr;

	temp = NULL;
	newstr = NULL;
	while (str[i])
	{
		// newstr = ft_strnstr(str, str, i);
		temp = check_dollars_heredoc(var, str, &i, y);
		// printf("i = %d\n", i);
		str = ft_strjoin(temp, str + i);
		i = ft_strlen(temp);
		free(temp);
		// printf("%d %s\n",i,  str);
		i++;
	}
	return (str);
}

int	ft_check_ctrl_c_heredoc(void)
{
	if(g_sig != SIGINT)
		return (1);
	return (0);
}

int	gest_heredoc(t_var *var, char *eof, int i)
{
	char	*line;
	char	*line2;
	int		fd;
	char	*file;

	g_sig = 1;
	file = ft_itoa(i);
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT | O_RDONLY, 00644);
	i = 0;
	rl_event_hook=ft_check_ctrl_c_heredoc;

	while (g_sig != SIGINT)
	{
		line = readline(">");
		if (line == NULL)
		{
			ft_ctrl_d_heredoc(var, eof);
			break;
		}
		i++;
		if (line && ((ft_strcmp(line, eof) == 0) || g_sig == SIGINT))
		{	
			free (line);
			if (g_sig == SIGINT)
			{
				unlink(file);
				free (file);
				file = ft_itoa(i*i);
				close (fd);
				fd = open(file, O_WRONLY | O_APPEND| O_CREAT | O_RDONLY, 00644);
			}
			break;
		}
		line = parse_all_str_heredoc(var, line, 0, 0);
		if (line != NULL)
			line2 = ft_strjoin(line, "\n");
		else
			line2 = ft_strdup("\n");
		ft_putstr_fd(line2, fd);
		if (line)
			free(line);
		if (line2)
			free(line2);
	}
	rl_event_hook = NULL;
	var->count_line += i;
	close (fd);
	g_sig = 0;
	fd = open(file, O_RDONLY);
	unlink(file);
	return (free(file), fd);
}

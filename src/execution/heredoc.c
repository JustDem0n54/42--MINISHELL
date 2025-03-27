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

char	*check_dollars_heredoc(t_var *var, char *str, int i, int y)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	*temp4;
	char	*cpy;

	cpy = NULL;
	temp = NULL;
	temp2 = NULL;
	temp3 = NULL;

	while(str[i] != '$' && i < (int)ft_strlen(str) && str[i])
		i++;
	if (str[i] == '$')
	{
		if (i > 0)
			temp = ft_substr(str, y, i - y);
		if (ft_isdigit(str[i + 1]) == 1)
		{
			i += 2;
			cpy = temp;
		}
		else if (str[i + 1] == '?')
		{
			cpy = ft_itoa(var->status);
			if (temp != NULL)
				cpy = ft_strjoin(temp, cpy);
			i += 2;

		}
		else if (ft_isalpha(str[i + 1]) == 1 || str[i + 1] == '_')
		{
			i++;
			y = i;
			while (ft_isalnum(str[i]) == 1 || str[i] == '_')
				i++;
			temp2 = check_export(var, str + y, i - y);
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
		}
		if (str[i] && ft_isalnum(str[i]) == 0)
			i++;
		y = i;
		if (str[i] != 0)
		{
			while (str[i])
				i++;
			temp3 = ft_substr(str, y, i - y);
			temp4 = cpy;
			// cpy = ft_strnjoin(2, (char *[]){temp4, temp3}, "");
			cpy = ft_strjoin(temp4, temp3);
			free(temp3);
			free(temp4);
		}
		// if (temp)
		// 	free(temp);
		// if (temp2)
		// 	free(temp2);
		// if (temp3)
		// 	free(temp3);
	}
	else
	{
		cpy = ft_strdup(str);
		free(str);
	}
	return (cpy);
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
		line = check_dollars_heredoc(var, line, 0, 0);
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

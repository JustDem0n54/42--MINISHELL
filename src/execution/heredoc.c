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
	while (1)
	{
		line = readline(">");
		i++;
		if (line == NULL)
		{
			ft_ctrl_d_heredoc(var, eof);
			break;
		}
		if (ft_strcmp(line, eof) == 0)
		{	
			free (line);
			break;
		}
		line2 = ft_strjoin(line, "\n");
		ft_putstr_fd(line2, fd);
		free(line);
		free(line2);
	}
	var->count_line += i;
	close (fd);
	fd = open(file, O_RDONLY);
	return (free(file), fd);
}
#include "../../minishell.h"


int	gest_heredoc(char *eof, int i)
{
	char	*line;
	char	*line2;
	int		fd;
	char	*file;

	file = ft_itoa(i);
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT | O_RDONLY, 00644);
	while (1)
	{
		line = readline(">");
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
	close (fd);
	fd = open(file, O_RDONLY);
	return (free(file), fd);
}
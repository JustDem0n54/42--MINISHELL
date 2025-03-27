#include "../../minishell.h"

int	check_input(t_var *var, char **cmd, int i)
{
	int	fd;

	fd = -1;
	while (cmd[i] && (ft_strcmp(cmd[i], "|") != 0))
	{
		if (ft_strcmp(cmd[i], "<") == 0)
		{
			fd = open(cmd[i + 1], O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("Brioshell: no such file or directory: ", 2);
				ft_putstr_fd(cmd[i + 1], 2);
				ft_putstr_fd("\n", 2);
				fd = -2;
			}
		}
		else if (ft_strcmp(cmd[i], "<<") == 0)
			fd = gest_heredoc(var, cmd[i + 1], i);
		i++;
	}
	return (fd);
}

int	check_output_append(char **cmd, int i)
{
	int	fd;

	fd = open(cmd[i + 1], O_CREAT | O_APPEND | O_WRONLY, 00644);
	if (fd == -1)
	{
		ft_putstr_fd("Brioshell : no such file or directory: ", 2);
		fd = -2;
	}
	return (fd);
}

int	check_output(char **cmd, int i)
{
	int	fd;

	fd = -1;
	while (cmd[i] && (ft_strcmp(cmd[i], "|") != 0))
	{
		if (ft_strcmp(cmd[i], ">") == 0)
		{
			fd = open(cmd[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 00644);
			if (fd == -1)
			{
				ft_putstr_fd("Brioshell : no such file or directory: ", 2);
				fd = -2;
			}
		}
		else if (ft_strcmp(cmd[i], ">>") == 0)
			fd = check_output_append(cmd, i);
		i++;
	}
	return (fd);
}

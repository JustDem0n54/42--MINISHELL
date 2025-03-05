#include "minishell.h"

int	ft_first_check(char **tab)
{
	if (ft_strchr(tab[0], '/') != NULL)
	{
		if (access(tab[0], X_OK) != 0)
		{
			ft_putstr_fd("no such file or directory: ", 2);
			ft_putstr_fd(tab[0], 2);
			ft_putstr_fd("\n", 2);
			// free_split(tab);
			return (exit (1), -1);
		}
		else
			return (0);
	}
	return (-1);
}

char	**ft_find_path(t_var *var)
{
	t_list	*temp;
	char	**chk_path;
	char	**path;
	int		i;

	temp = var->updt_env;
	while (temp)
	{
		if (strncmp((char *)temp->content, "PATH=", 5) == 0)
			break ;
		temp = temp->next;
	}
	chk_path = ft_split((char *)temp->content + 5, ':');
	i = 0; /*a revoir*/
	while (chk_path[i])
		i++;
	path = ft_calloc(i + 1, sizeof(char **));
	i = 0;
	while (chk_path[i])
	{
		path[i] = ft_strjoin(chk_path[i], "/");
		free (chk_path[i]);
		i++;
	}
	free (chk_path);
	return (path);
}

char	*ft_check_cmd(char **path, char **tab)
{
	char	*path_cmd;
	int		j;

	j = 0;
	path_cmd = ft_strjoin(path[j], tab[0]);
	while (path[j + 1] && access(path_cmd, X_OK) != 0)
	{
		free(path_cmd);
		j++;
		path_cmd = ft_strjoin(path[j], tab[0]);
	}
	free_split(path);
	if (access(path_cmd, X_OK) != 0)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd("\n", 2);
		free(path_cmd);
		// free_split(tab);
		return (exit (1), NULL);
	}
	return (path_cmd);
}

char	**ft_check_opt(char *path_cmd, char **tab)
{
	// free (tab[0]); /*ajouter free quand fusion ds codes*/
	tab[0] = ft_strdup(path_cmd);
	return (tab);
}

void	ft_exe(t_var *var, char **tab)
{
	char	**path;
	char	*path_cmd;
	char	**path_opt;
	
	if (ft_first_check(&tab[0]) == 0)
	{
		if (execve(tab[0], tab, NULL) == -1)
			return (perror("error first check cmd"), exit (1));
		// free_split(tab);
	}
	else
	{
		path = ft_find_path(var);
		path_cmd = ft_check_cmd(path, tab);
		path_opt = ft_check_opt(path_cmd, tab);
		if (execve(path_cmd, path_opt, NULL) == -1)
		{
			free(path_cmd);
			free_split(path_opt);
			return (perror("error execve"), exit (1));
		}
	}
}

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
			return (-1);
		}
		else
			return (0);
	}
	return (-1);
}

// char	**ft_find_path(t_var *var)
// {
// 	t_list	*temp;
// 	char	**chk_path;
// 	char	**path;
// 	int		i;

// 	temp = var->updt_env;
// 	while (temp)
// 	{
// 		if (strncmp((char *)temp->content, "PATH=", 5) == 0)
// 			break ;
// 		temp = temp->next;
// 	}
// 	chk_path = ft_split((char *)temp->content + 5, ':');
// 	i = 0; /*a revoir*/
// 	while (chk_path[i])
// 		i++;
// 	path = ft_calloc(i + 1, sizeof(char **));
// 	i = 0;
// 	while (chk_path[i])
// 	{
// 		path[i] = ft_strjoin(chk_path[i], "/");
// 		free (chk_path[i]);
// 		i++;
// 	}
// 	free (chk_path);
// 	return (path);
// }

// char	*ft_check_cmd(char **path, char **tab)
// {
// 	char	*path_cmd;
// 	int		j;

// 	j = 0;
// 	path_cmd = ft_strjoin(path[j], tab[0]);
// 	while (path[j + 1] && access(path_cmd, X_OK) != 0)
// 	{
// 		free(path_cmd);
// 		j++;
// 		path_cmd = ft_strjoin(path[j], tab[0]);
// 	}
// 	free_split(path);
// 	if (access(path_cmd, X_OK) != 0)
// 	{
// 		ft_putstr_fd("command not found: ", 2);
// 		ft_putstr_fd(tab[0], 2);
// 		ft_putstr_fd("\n", 2);
// 		free(path_cmd);
// 		// free_split(tab);
// 		return (NULL);
// 	}
// 	return (path_cmd);
// }

char	*check_path(char **env, char *cmd)
{
	int		i;
	char	**path;
	char	*temp;

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

char	**ft_check_opt(char *path_cmd, char **tab)
{
	// free (tab[0]); /*ajouter free quand fusion ds codes*/
	tab[0] = ft_strdup(path_cmd);
	return (tab);
}

char	**check_command(char **tab, t_var *var)
{
	char	**cmd;
	int		j;
	int 	i;

	j = var->cmd_count;
	i = 0;
	while (tab[var->cmd_count] && ft_strcmp(tab[var->cmd_count], "|") != 0)
		var->cmd_count++;
	cmd = malloc(sizeof(char *) * (var->cmd_count - j + 1));
	while (j < var->cmd_count)
	{
		cmd[i] = ft_strdup(tab[j]);
		i++;
		j++;
	}
	var->cmd_count++;
	return (cmd);
}

int	count_command(char **tab)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "|") == 0)
			count++;
		i++;
	}
	return (count + 1);
}

char	**do_env(t_list *env)
{
	char	**nenv;
	int		i;

	i = 0;
	nenv = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	while (env)
	{
		nenv[i] = env->content;
		i++;
		env = env->next;
	}
	nenv[i] = 0;
	return (nenv);
}

void	exec_pid(t_var *var, char **tab)
{
	char **cmd;
	int i;
	// int	*pipefd;
	pid_t	pid;
	char **env;
	char *path_cmd;

	var->cmd_count = 0;
	var->nbcmd = count_command(tab);
	i = 0;
	// pipefd = 0;
	env = do_env(var->env);
	while (i < var->nbcmd)
	{
		cmd = check_command(tab, var);
		// if (pipe(pipefd) == -1)
		// 	return ;
		pid = fork();
		if (pid == 0)
		{
			if (ft_first_check(&cmd[0]) == 0)
			{
				if (execve(tab[0], tab, NULL) == -1)
					return (perror("error first check cmd"));
				free_split(cmd);
			}
			else
			{
				path_cmd = check_path(env, cmd[0]);
				if (path_cmd == NULL)
					return ;
				if (execve(path_cmd, cmd, NULL) == -1)
				{
					free(path_cmd);
					free_split(cmd);
					return (perror("error execve"));
				}
			}
		}
		i++;
		waitpid(pid, 0, 0);
	}
	
}
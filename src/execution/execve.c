#include "../../minishell.h"

int	ft_first_check(char **tab)
{
	if (ft_strchr(tab[0], '/') != NULL)
	{
		if (access(tab[0], X_OK) != 0)
		{
			ft_putstr_fd("no such file or directory: ", 2);
			ft_putstr_fd(tab[0], 2);
			ft_putstr_fd("\n", 2);
			return (-1);
		}
		else
			return (0);
	}
	return (-1);
}

char	*check_path(char **env, char *cmd)
{
	int		i;
	char	**path;
	char	*temp;

	if (cmd == NULL || env == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
	}
	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
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

int	count_element(char **tab, int i)
{
	int count;

	count = 0;
	while (tab[i] && ft_strcmp(tab[i], "|") != 0)
	{
		if (ft_strcmp(tab[i], "<") == 0 || ft_strcmp(tab[i], ">") == 0)
			i += 2;
		if (tab[i] && ft_strcmp(tab[i], "|") != 0)
		{
			count++;
			i++;
		}
	}
	return(count);
}

char	**check_command(char **tab, t_var *var, t_exec *exec)
{
	char	**cmd;
	int		i;

	i = 0;
	exec->input = check_input(tab, var->cmd_count);
	exec->output = check_output(tab, var->cmd_count);
	cmd = malloc(sizeof(char *) * (count_element(tab, var->cmd_count) + 1));
	while (tab[var->cmd_count] && ft_strcmp(tab[var->cmd_count], "|") != 0)
	{
		if (ft_strcmp(tab[var->cmd_count], "<") == 0
			|| ft_strcmp(tab[var->cmd_count], ">") == 0)
			var->cmd_count += 2;
		if (tab[var->cmd_count] && ft_strcmp(tab[var->cmd_count], "|") != 0)
		{
			cmd[i++] = ft_strdup(tab[var->cmd_count]);
			var->cmd_count++;
		}
	}
	cmd[i] = NULL;
	var->cmd_count++;
	return (cmd);
}

// char	**check_command(char **tab, t_var *var, t_exec *exec)
// {
// 	int		j;
// 	int 	i;
// 	char	**cmd;

	
// 	i = 0;
// 	j = var->cmd_count;
// 	while (tab[var->cmd_count] && (ft_strcmp(tab[var->cmd_count], "|") != 0
// 		&& ft_strcmp(tab[var->cmd_count], "<") != 0
// 		&& ft_strcmp(tab[var->cmd_count], ">") != 0))
// 		var->cmd_count++;
// 	exec->input = check_input(tab, var);
// 	exec->output = check_output(tab, var);
// 	cmd = malloc(sizeof(char *) * (var->cmd_count - j + 1));
// 	while (j < var->cmd_count)
// 	{
// 		cmd[i] = ft_strdup(tab[j]);
// 		i++;
// 		j++;
// 	}
// 	cmd[i] = NULL;
// 	while (tab[var->cmd_count] && ft_strcmp(tab[var->cmd_count], "|") != 0)
// 		var->cmd_count++;
// 	var->cmd_count++;	
// 	return (cmd);
// }

int	count_command(char **tab)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "|") == 0 && ft_strcmp(tab[i - 1], "|") != 0)
			count++;
		if (ft_strcmp(tab[i], "|") == 0 && tab[i + 1] == NULL)
			return (count);
		i++;
	}
	return (count + 1);
}

char	**do_env(t_list *env)
{
	char	**nenv;
	t_list	*temp;
	int		i;

	i = 0;
	nenv = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	temp = env;
	while (temp)
	{
		nenv[i] = ft_strdup((char *)temp->content);
		i++;
		temp = temp->next;
	}
	nenv[i] = 0;
	return (nenv);
}

void	(*ft_cmd(char **cmd))(t_var *var, char **tab)
{
	if (cmd[0] == NULL)
		return (NULL);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset);
	return (NULL);
}

void	exec_all(t_var *var, t_exec *exec, char **env)
{
	void	(*builtins)(t_var *, char **);

	builtins = ft_cmd(exec->cmd);
	if (builtins == NULL)
	{
		if (exec->path == NULL)
		{
			ft_putstr_fd(exec->cmd[0], 1);
			ft_putstr_fd(": command not found\n", 1);
			free_split(env);
			ft_free_all(var);
			exit(1);
		}
		if (execve(exec->path, exec->cmd, env) == -1)
			return (perror("error execve"), free_split(env), ft_free_all(var), exit (1));
	}
	else
	{
		builtins(var, exec->cmd);
		free_split(env);
		ft_free_all(var);
	}
	exit(0);
}

void	setup_dup2_and_close(t_exec *exec, int *fd)
{
	if (exec->input != 0)
	{
		dup2(exec->input, STDIN_FILENO);
		close(exec->input);
	}
	if (exec->output != 1)
	{
		dup2(exec->output, STDOUT_FILENO);
		close(exec->output);
	}
	close(fd[0]);
}

void	wait_all_pid(t_var *var, pid_t *pids)
{
	int i;
	
	i = 0;
	while (i < var->nbcmd)
	{
		waitpid(pids[i], &var->status, 0);
		i++;
	}
}

void	select_input(t_exec *exec, int i, int *prevfd)
{
	if (i == 0 && exec->input == -1)
		exec->input = 0;
	else if (i > 0 && exec->input == -1)
		exec->input = *prevfd;
}

void	select_output(int *fd, t_exec *exec, int i, t_var *var)
{
	if (i == var->nbcmd - 1 && exec->output == -1)
		exec->output = 1;
	else if (i != var->nbcmd - 1 && exec->output == -1)
		exec->output = fd[1];
}

void	setup_exec(t_var *var, t_exec *exec)
{
	pid_t	*pids;
	int		fd[2];
	int		i;
	int		prevfd;
	char	**env;

	env = do_env(var->env);
	i = 0;
	prevfd = -1;
	pids = ft_calloc(var->nbcmd, sizeof(pid_t));
	while (i < var->nbcmd)
	{
		if (i != var->nbcmd - 1)
			pipe(fd);
		select_input(exec, i, &prevfd);
		select_output(fd, exec, i, var);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			setup_dup2_and_close(exec, fd);
			free(pids);
			if (exec->input == -2 || exec->output == -2)
				exit(1);
			exec_all(var, exec, env);
			
		}
		if (prevfd != -1)
			close(prevfd);
		close(fd[1]);
		prevfd = fd[0];
		exec = exec->next;
		i++;
	}
	close(prevfd);
	close(fd[0]);
	close(fd[1]);
	wait_all_pid(var, pids);
	free(pids);
	free_split(env);

}

void	setup_dup2(t_exec *exec)
{
	if (exec->input != 0)
	{
		dup2(exec->input, STDIN_FILENO);
		close(exec->input);
	}
	if (exec->output != 1)
	{
		dup2(exec->output, STDOUT_FILENO);
		close(exec->output);
	}
}

void	exec_one(t_var *var, t_exec *exec)
{
	pid_t	pid;
	char	**env;

	env = do_env(var->env);
	pid = fork();
	if (pid == 0)
	{
		if (exec->path == NULL)
		{
			ft_putstr_fd(exec->cmd[0], 1);
			ft_putstr_fd(": command not found\n", 2);
			free_split(env);
			ft_free_all(var);
			exit(1);
		}
		setup_dup2(exec);
		if (execve(exec->path, exec->cmd, env) == -1)
			return (free_split(env), perror(exec->cmd[0]),
				ft_free_all(var), exit (1));
	}
	waitpid(pid, &var->status, 0);
	free_split(env);
	return ;
}

void	execution(t_var *var, t_exec *exec)
{
	void	(*builtins)(t_var *, char **);
	int		i;
	int		save;
	
	i = 0;
	save = 0;
	if (var->nbcmd == 1)
	{
		if (exec->output == -1)
			exec->output = 1;
		if (exec->input == -1)
			exec->input = 0;
		builtins = ft_cmd(exec->cmd);
		if (builtins == NULL)
			exec_one(var, exec);
		else
		{
			if (exec->input != -1)
				close(exec->input);
			exec->input = 0;
			save = dup(1);
			setup_dup2(exec);
			builtins(var, exec->cmd);
			dup2(save, 1);
			close(save);
		}
		return ;
	}
	setup_exec(var, exec);
}

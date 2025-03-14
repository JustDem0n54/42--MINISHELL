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
			return (cmd);
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

char	**check_command(char **tab, t_var *var)
{
	int		j;
	int 	i;
	char	**cmd;

	
	i = 0;
	while (tab[var->cmd_count] && ft_strcmp(tab[var->cmd_count], "|") == 0)
		var->cmd_count++;
	j = var->cmd_count;
	while (tab[var->cmd_count] && ft_strcmp(tab[var->cmd_count], "|") != 0)
		var->cmd_count++;
	cmd = malloc(sizeof(char *) * (var->cmd_count - j + 1));
	while (j < var->cmd_count)
	{
		
		cmd[i] = ft_strdup(tab[j]);
		// printf("dans check %s\n", cmd[i]);
		i++;
		j++;
	}
	cmd[i] = NULL;
	// printf("dans check %s\n", cmd[i]);
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
	// else if (ft_strcmp(cmd[0], "exit") == 0)
	// 	return (ft_exit);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset);
	return (NULL);
}

void	exec_all(t_var *var, t_exec *exec, char **env)
{
	void	(*builtins)(t_var *, char **);
	
	// putstr("cmd[0] %s\n", exec->cmd[0]);
	builtins = ft_cmd(exec->cmd);
	if (builtins == NULL)
		execve(exec->path, exec->cmd, env);
	else
		builtins(var, exec->cmd);
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
	pids = ft_calloc(var->nbcmd, sizeof(pids));
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
	free(env);
}

void	exec_one(t_var *var, t_exec *exec)
{
	pid_t	pid;
	char	**env;

	env = do_env(var->env);
	pid = fork();
	exec->input = 0;
	exec->output = 1;
	if (pid == 0)
	{
		execve(exec->path, exec->cmd, env);
		exit(1);
	}
	waitpid(pid, &var->status, 0);
	free(env);
	return ;
}

void	execution(t_var *var, t_exec *exec)
{
	void	(*builtins)(t_var *, char **);
	int		i;
	
	i = 0;
	// printf("cmd %s\n", exec->cmd[0]);
	// printf("cmd %s\n", exec->cmd[1]);
	if (var->nbcmd == 1)
	{
		builtins = ft_cmd(exec->cmd);
		if (builtins == NULL)
			exec_one(var, exec);
		else
			builtins(var, exec->cmd);
		return ;
	}
	setup_exec(var, exec);
}

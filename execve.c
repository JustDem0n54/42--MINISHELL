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

void	(*ft_cmd(char **cmd))(t_var *var, char **tab)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo);
	// else if (ft_strcmp(cmd[0], "pwd") == 0)
	// 	return (ft_pwd);
	// else if (ft_strcmp(cmd[0], "cd") == 0)
	// 	return (ft_cd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env);
	// else if (ft_strcmp(tab[0], "exit") == 0)
	// 	return (ft_exit());
	// else if (ft_strcmp(tab[0], "unset") == 0)
	// 	return (ft_unset());
	return (NULL);
}

void	setup_pid(t_var *var, char **tab)
{
	int		pipefd[2];
	pid_t	pid;
	int i;
	char	**env;
	char	*path;
	char	**cmd;

	i = 1;
	env = do_env(var->env);
	var->entry = 0;
	var->output = 1;
	while (i <= var->nbcmd)
	{
		if (pipe(pipefd) == -1)
			return (ft_putstr_fd("Error pipe.", 2));
		var->output = pipefd[1];
		if (i == var->nbcmd)
			var->output = STDOUT_FILENO;
		if (var->entry != -1 && var->output != -1)
			pid = fork();
		ft_putnbr_fd(var->output, 1);
		if (pid == 0)
		{
			if (i > 1)
			{
				if (dup2(var->entry, STDIN_FILENO) == -1)
					return (ft_putstr_fd("Error dup2.", 2), exit(1));
			}
			if (i < var->nbcmd)
			{
				if (dup2(var->output, STDOUT_FILENO) == -1)
					return (ft_putstr_fd("Error dup2.", 2), exit(1));
			}
			close(var->entry);
			close(pipefd[0]);
			close(pipefd[1]);
			cmd = check_command(tab, var);
			path = check_path(env, cmd[0]);
			execve(path, cmd, env);
			exit(EXIT_FAILURE);
		}
		close(var->entry);
		close(var->output);
		var->entry = pipefd[0];
		i++;
		wait(NULL);
	}
	return ;
}

void	exec_one(t_var *var, char **cmd)
{
	char	*path;
	char	**env;
	pid_t	pid;

	env = do_env(var->env);
	path = check_path(env, cmd[0]);
	pid = -1;
	pid = fork();
	if (pid == 0)
		execve(path, cmd, env);
	wait(NULL);
}

void	execution(t_var *var, char **tab)
{
	char **cmd;
	int i;
	void	(*exec)(t_var *, char **);
	int	*pipefd;

	var->cmd_count = 0;
	var->nbcmd = count_command(tab);
	i = 1;
	pipefd = 0;
	if (var->nbcmd == 1)
	{
		cmd = check_command(tab, var);
		exec = ft_cmd(cmd);
		if (exec == NULL)
			return (exec_one(var, cmd));
		exec(var, cmd);
		return ;
	}
	else
		setup_pid(var, tab);
}

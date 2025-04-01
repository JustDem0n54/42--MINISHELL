#include "../../minishell.h"

void	close_fd(int *fd, int prevfd, int i, t_exec *exec)
{
	if (i == 0)
	{
		close(prevfd);
		close(fd[0]);
		close(fd[1]);
	}
	else if (i < 0)
	{
		if (prevfd > -1)
			close(prevfd);
		close(fd[1]);
		if (exec->input > 0)
			close(exec->input);
		if (exec->output > 1)
			close(exec->output);
	}
}

void	exec_all(t_var *var, t_exec *exec, char **env)
{
	void	(*builtins)(t_var *, char **);
	int		status;

	status = 0;
	builtins = ft_cmd(exec->cmd);
	if (builtins == NULL)
	{
		if (exec->path == NULL)
			ft_error_path_cmd(var, exec, env);
		if (execve(exec->path, exec->cmd, env) == -1)
		{
			return (perror("error execve"), free_split(env),
				ft_free_all(var), exit(126));
		}
	}
	else
	{
		builtins(var, exec->cmd);
		status = var->status;
		free_split(env);
		ft_free_all(var);
	}
	exit(status);
}

void	do_pids(t_exec *exec, pid_t *pids, int *fd, t_var *var)
{
	char	**env;

	env = convert_env(var->env);
	setup_dup2_and_close(exec, fd);
	free(pids);
	if (exec->input == -2 || exec->output == -2)
		return (ft_free_all(var), free_split(env), exit(1));
	exec_all(var, exec, env);
}


char	**convert_env(t_list *env)
{
	char	**nenv;
	t_list	*temp;
	int		i;

	i = 0;
	if (env == NULL)
		return (NULL);
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

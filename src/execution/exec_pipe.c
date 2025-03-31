#include "../../minishell.h"

void	exec_all(t_var *var, t_exec *exec, char **env)
{
	void	(*builtins)(t_var *, char **);
	int		status;

	builtins = ft_cmd(exec->cmd);
	if (builtins == NULL)
	{
		if (exec->path == NULL)
			ft_error_path_cmd(var, exec, env);
		if (execve(exec->path, exec->cmd, env) == -1)
		{
			status = 126;
			return (perror("error execve"), free_split(env),
				ft_free_all(var), exit (status));
		}
	}
	else
	{
		builtins(var, exec->cmd);
		free_split(env);
		ft_free_all(var);
	}
	exit(0);
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

char	**convert_env(t_list *env)
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

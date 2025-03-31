#include "../../minishell.h"

void	setup_dup2_and_close(t_exec *exec, int *fd)
{
	if (exec->input > 0)
	{
		dup2(exec->input, STDIN_FILENO);
		close(exec->input);
	}
	if (exec->output > 1)
	{
		dup2(exec->output, STDOUT_FILENO);
		close(exec->output);
	}
	close(fd[0]);
}

void	wait_all_pid(t_var *var, pid_t *pids)
{
	int	i;

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
			do_pids(exec, pids, fd, var);
		close_fd(fd, prevfd, i - var->nbcmd, exec);
		prevfd = fd[0];
		exec = exec->next;
		i++;
	}
	close_fd(fd, prevfd, i - var->nbcmd, exec);
	wait_all_pid(var, pids);
	free(pids);
}

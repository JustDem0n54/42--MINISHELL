#include "../../minishell.h"

t_exec	*ft_execnew(void)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (new == NULL)
		return (NULL);
	new->cmd = NULL;
	new->input = 0;
	new->output = 1;
	new->path = NULL;
	new->next = NULL;
	return (new);
}

t_exec	*exec_last(t_exec *exec)
{
	if (exec == NULL)
		return (NULL);
	while (exec && exec->next)
		exec = exec->next;
	return (exec);
}

void	exec_add_back(t_exec **exec, t_exec *new)
{
	t_exec	*temp;

	if (exec == NULL || new == NULL)
		return ;
	if (*exec == NULL)
	{
		*exec = new;
		return ;
	}
	temp = exec_last(*exec);
	temp->next = new;
}

t_exec	*init_exec(t_var *var, char **tab)
{
	int		i;
	char	**env;
	t_exec	*exec;
	t_exec	*temp;

	var->cmd_count = 0;
	var->nbcmd = count_command(tab);
	i = -1;
	env = do_env(var->env);
	exec = ft_execnew();
	while (++i < var->nbcmd)
		exec_add_back(&exec, ft_execnew());
	temp = exec;
	while (temp->next)
	{
		temp->cmd = check_command(tab, var);
		if (ft_cmd(temp->cmd) == NULL)
			temp->path = check_path(env, temp->cmd[0]);
		temp->input = -1;
		temp->output = -1;
		temp = temp->next;
	}
	return (free_split(env), exec);
}

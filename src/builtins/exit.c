#include "../../minishell.h"

void	ft_free_exec(t_exec *exec)
{
	t_exec	*temp;

	if (exec == NULL)
		return ;
	while (exec)
	{
		temp = exec->next;
		if (exec->cmd)
		{
			free_split(exec->cmd);
			exec->cmd = NULL;
		}
		if (exec->path != NULL)
			free(exec->path);
		free(exec);
		exec = NULL;
		exec = temp;
	}
}

void	ft_free_all(t_var *var)
{
	ft_free_exec(var->exec);
	if (var->parse != NULL)
		ft_lstclear(&(var->parse), free);
	if (var->data != NULL)
		free_split(var->data);
	if (var->env != NULL)
		ft_lstclear(&(var->env), free);
	if (var->pwd != NULL)
		free (var->pwd);
	if (var->oldpwd != NULL)
		free (var->oldpwd);
	if (var->home != NULL)
		free (var->home);
	var->parse = NULL;
	var->data = NULL;
	var->env = NULL;
	var->pwd = NULL;
	var->oldpwd = NULL;
	var->home = NULL;
	free(var);
	rl_clear_history();
}

void	error_message_exit_two_arg(t_var *var, char **tab)
{
	ft_putstr_fd(tab[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(tab[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("numeric argument required\n", 2);
	ft_free_all(var);
	var->status = 2;
	exit(var->status);
}

void	ft_exit(t_var *var, char **tab)
{
	printf("exit\n");
	if (tab[1] && ft_strcmp(ft_litoa(ft_atol(tab[1])), tab[1]) != 0)
		error_message_exit_two_arg(var, tab);
	else if (tab[1] && tab[2])
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		var->status = 127;
		return ;
	}
	else
	{
		if (tab && tab[1])
		{
			ft_free_all(var);
			exit(ft_atol(tab[1]) % 256);
		}
		else
		{
			ft_free_all(var);
			exit(EXIT_SUCCESS);
		}
	}
}

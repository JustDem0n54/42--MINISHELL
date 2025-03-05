#include "minishell.h"

t_list	*init_env(char **env)
{
	int		i;
	t_list	*lst_env;

	i = 0;
	lst_env = NULL;
	while (env[i])
	{
		ft_lstadd_back(&lst_env, ft_lstnew(ft_strdup(env[i])));
		i++;
	}
	return (lst_env);
}

void	init_struct(t_var *var, char **env)
{
	ft_bzero(var, sizeof(t_var));
	var->updt_env = init_env(env);
	var->check_export = 0; /*a supp car bzero*/
	return ;
}

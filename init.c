#include "minishell.h"

t_list	*init_env(char **env)
{
	int		i;
	t_list	*lst_env;

	i = 0;
	lst_env = NULL;
	while (env[i])
	{
		ft_lstadd_back(&lst_env, ft_lstnew(env[i]));
		i++;
	}
	return (lst_env);
}

t_var	*init_struct(t_var *var, char **env)
{
	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->init_env = init_env(env);
	var->updt_env = var->init_env;
	var->export = NULL;
	var->check_export = 0;
	var->data = NULL;
	return (var);
	// ne pas oublier de free var->updt_env et var
}

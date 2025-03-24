#include "../../minishell.h"

t_list	*create_env(t_var *var, t_list **lst_env)
{
	ft_lstadd_back(lst_env, ft_lstnew(ft_strjoin("PWD=", getcwd(NULL, 0))));
	var->pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	ft_lstadd_back(lst_env, ft_lstnew(ft_strdup("SHLVL=1")));
	ft_lstadd_back(lst_env, ft_lstnew(ft_strdup("_=/usr/bin/env")));
	return(*lst_env);;
}

t_list	*init_env(t_var *var, char **env)
{
	int		i;
	t_list	*lst_env;

	i = 0;
	lst_env = NULL;
	if (!env[i])
		return(create_env(var, &lst_env));
	while (env[i])
	{
		ft_lstadd_back(&lst_env, ft_lstnew(ft_strdup(env[i])));
		if (ft_strncmp(env[i], "PWD", 3) == 0)
			var->pwd = ft_strdup(env[i]);
		if (ft_strncmp(env[i], "OLDPWD", 6) == 0)
			var->oldpwd = ft_strdup(env[i]);
		if (ft_strncmp(env[i], "HOME", 4) == 0)
			var->home = ft_strdup(env[i]);
		i++;
	}
	return (lst_env);
}

t_var	*init_struct(t_var *var, char **env)
{
	var = malloc(sizeof(t_var));
	ft_bzero(var, sizeof(t_var));
	var->env = init_env(var, env);
	return (var);
}

// gerer env -i : PAS PATH 
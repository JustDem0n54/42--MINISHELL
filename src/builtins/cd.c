#include "../../minishell.h"

void	error_unset(t_var *var, char **tab)
{
	if (tab[1] && ft_strcmp(tab[1], "-") == 0)
		return (var->status = 1, ft_putstr_fd(tab[0], 2),
			ft_putstr_fd(": OLDPWD not set\n", 2));
	else if (!var->home)
	{
		ft_putstr_fd(tab[0], 2);
		if (tab[1])
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(tab[1], 2);
		}
		ft_putstr_fd(": HOME not set\n", 2);
	}
	var->status = 1;
	return ;
}

void	update_env_pwd_and_old_(t_var *var)
{
	t_list	*temp;

	temp = var->env;
	while (var->env)
	{
		if (ft_strncmp((char *)var->env->content, "PWD=", 4) == 0)
		{
			free (var->env->content);
			var->env->content = ft_strdup((char *)var->pwd);
		}
		else if (ft_strncmp((char *)var->env->content, "OLDPWD=", 7) == 0)
		{
			free (var->env->content);
			var->env->content = ft_strdup((char *)var->oldpwd);
		}
		var->env = var->env->next;
	}
	var->env = temp;
	return ;
}

void	cd_home(t_var *var, char **tab)
{
	if (!var->home)
		return (error_unset(var, tab));
	if (chdir(var->home + 5) != 0)
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(var->home + 5, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		var->status = 1;
		return ;
	}
	var->status = 0;
	return ;
}

void	ft_cd(t_var *var, char **tab)
{
	if (tab[1] && tab[2])
		return (var->status = 1, ft_putstr_fd(tab[0], 2),
			ft_putstr_fd(": too many arguments\n", 2));
	if (!tab[1] || ft_strcmp(tab[1], "~") == 0)
		return (cd_home(var, tab));
	else if (ft_strcmp(tab[1], "-") == 0)
	{
		if (!var->oldpwd)
			return (var->status = 1, error_unset(var, tab));
		tab[1] = ft_strdup(var->oldpwd + 7);
	}
	if (chdir(tab[1]) != 0)
		return (var->status = 1, ft_putstr_fd(tab[0], 2),
			ft_putstr_fd(": ", 2), perror(tab[1]));
	if (var->oldpwd != NULL)
		free (var->oldpwd);
	var->oldpwd = ft_strjoin("OLD", ft_strdup(var->pwd));
	ft_pwd(var, tab);
	update_env_pwd_and_old_(var);
	var->status = 0;
	return ;
}

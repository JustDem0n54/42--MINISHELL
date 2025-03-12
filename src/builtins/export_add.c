#include "../../minishell.h"

void	ft_error_var_env(char **tab, int i)
{
	ft_putstr_fd(tab[i], 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(tab[i], 2);
	return (ft_putstr_fd("': not a valid identifier\n", 2));
}

int	check_var_env_added(t_var *var, char *tab, int i)
{
	t_list	*temp;

	temp = var->env;
	while (var->env)
	{
		if (strncmp(tab, "PWD=", 4) == 0
			|| strncmp(tab, "OLDPWD=", 7) == 0)
			return (var->env = temp, 1);
		else if (strncmp(var->env->content, tab, i) == 0)
		{
			if (strncmp(tab, "HOME=", 5) == 0)
			{
				free(var->home);
				var->home = ft_strdup(tab);
			}
			free (var->env->content);
			var->env->content = ft_strdup(tab);
			return (var->env = temp, 1);
		}
		else
			var->env = var->env->next;
	}
	var->env = temp;
	return (0);
}

void	add_var_env(t_var *var, char **tab)
{
	int		i;
	size_t	j;

	i = 1;
	j = 0;
	while (tab[i])
	{
		if (ft_isalpha(tab[i][0]) == 0 && tab[i][0] != '_')
			ft_error_var_env(tab, i);
		j = var_name_length(tab[i]);
		if (tab[i][j] != '=')
			return (ft_error_var_env(tab, i));
		else if (check_var_env_added(var, tab[i], j) == 0)
			ft_lstadd_back(&var->env, ft_lstnew(ft_strdup(tab[i])));
		j = 0;
		i++;
	}
}

void	increase_shlvl(t_var *var)
{
	t_list	*temp;
	char	*temp2;

	temp = var->env;
	while (var->env)
	{
		if (strncmp(var->env->content, "SHLVL=", 6) == 0)
		{
			temp2 = ft_strdup((char *)var->env->content + 6);
			free (var->env->content);
			var->env->content = ft_strjoin("SH"
					"LVL=", ft_itoa(ft_atoi(temp2) + 1));
			var->env = temp;
			return ;
		}
		else
			var->env = var->env->next;
	}
	var->env = temp;
	return ;
}

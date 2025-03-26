#include "../../minishell.h"

size_t	var_name_len(char *tab)
{
	size_t	j;

	j = 0;
	while (tab[j] && tab[j + 1] && tab[j + 1] != '='
		&& (ft_isalnum(tab[j]) == 1 || tab[j] == '_'))
		j++;
	return (j + 1);
}

void	check_var_env_unset(t_var *var, char *tab)
{
	if (strncmp(tab, "HOME", ft_strlen(tab)) == 0)
	{
		free (var->home);
		var->home = NULL;
	}
	else if (strncmp(tab, "OLDPWD", ft_strlen(tab)) == 0)
	{
		free (var->oldpwd);
		var->oldpwd = NULL;
	}
	return ;
}

int	unset_first(t_var *var, char *tab, t_list *temp, int len)
{
	int len_env;

	len_env = var_name_len((char *)var->env->content);
	if (var->env && len_env == len && ft_strncmp(tab,
			(char *)var->env->content, len) == 0)
	{
		check_var_env_unset(var, tab);
		temp = var->env->next;
		free (var->env->content);
		free (var->env);
		var->env = temp;
		return (0);
	}
	return (1);
}

int	unset_between(t_var *var, char *tab, t_list *temp, int len)
{
	t_list	*temp2;
	int len_env;

	len_env = var_name_len((char *)var->env->next->content);
	check_var_env_unset(var, tab);
	if (var->env->next && len_env == len && ft_strncmp(tab,
			(char *)var->env->next->content, len) == 0)
	{
		if (var->env->next->next)
		{
			temp2 = var->env->next->next;
			free (var->env->next->content);
		}
		else
			temp2 = NULL;
		free (var->env->next);
		var->env->next = temp2;
		var->env = temp;
		return (0);
	}
	return (1);
}

void	ft_unset(t_var *var, char **tab)
{
	t_list	*temp;
	int		i;

	i = 1;
	temp = var->env;
	while (tab[i])
	{
		if (var_name_len(tab[i]) != ft_strlen(tab[i]))
		{
			var->status = 0;
			return ;
		}
		if (unset_first(var, tab[i], temp, var_name_len(tab[i])) == 1)
		{
			while (var->env && var->env->next)
			{
				if (unset_between(var, tab[i], temp, var_name_len(tab[i])) == 0)
					break ;
				else
					var->env = var->env->next;
			}
		}
		var->env = temp;
		i++;
	}
	var->status = 0;
	var->env = temp;
}

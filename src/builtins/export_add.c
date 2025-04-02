/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:43:14 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/02 13:43:15 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_error_var_env(t_var *var, char **tab, int i)
{
	var->status = 1;
	ft_putstr_fd("Brioshell: ", 2);
	ft_putstr_fd(tab[0], 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(tab[i], 2);
	return (ft_putstr_fd("': not a valid identifier\n", 2));
}

int	first_check(t_var *var, char *tab)
{
	if (ft_strncmp(tab, "_=", 2) == 0)
		return (0);
	else
	{
		if (ft_strncmp(tab, "HOME=", 5) == 0)
		{
			free(var->home);
			var->home = ft_strdup(tab);
		}
	}
	return (1);
}

int	check_var_env_added(t_var *var, char *s, size_t i)
{
	t_list	*temp;

	temp = var->env;
	if (first_check(var, s) == 0)
		return (var->status = 0, var->env = temp, 1);
	if (ft_strchr(s, '=') != NULL && var_name_len(s) != (ft_strlen(s)
			- ft_strlen(ft_strchr(s, '='))))
		return (var->status = 1, var->env = temp, 1);
	while (var->env)
	{
		if (var_name_len((char *)var->env->content) == i
			&& ft_strncmp((char *)var->env->content, s, i) == 0)
		{
			if (!s[i] || (s[i] && s[i] != '='))
				return (var->status = 0, var->env = temp, 2);
			free (var->env->content);
			var->env->content = ft_strdup(s);
			return (var->status = 0, var->env = temp, 2);
		}
		else
			var->env = var->env->next;
	}
	var->env = temp;
	return (var->status = 0, 0);
}

void	add_var_env(t_var *var, char **tab)
{
	int		i;
	size_t	j;

	i = 1;
	j = 0;
	while (tab[i])
	{
		j = var_name_len(tab[i]) - 1;
		if (ft_strcmp(tab[i], "") != 0
			&& (ft_isalpha(tab[i][0]) == 0 && tab[i][0] != '_'))
			ft_error_var_env(var, tab, i);
		else if (check_var_env_added(var, tab[i], j + 1) == 0)
		{
			var->status = 0;
			ft_lstadd_back(&var->env, ft_lstnew(ft_strdup(tab[i])));
		}
		else if (check_var_env_added(var, tab[i], j + 1) == 1)
			ft_error_var_env(var, tab, i);
		j = 0;
		i++;
	}
}

void	increase_shlvl(t_var *var)
{
	t_list	*temp;
	char	*temp2;
	char	*temp3;

	temp = var->env;
	while (var->env)
	{
		if (strncmp(var->env->content, "SHLVL=", 6) == 0)
		{
			temp2 = ft_strdup((char *)var->env->content + 6);
			temp3 = ft_itoa(ft_atoi(temp2) + 1);
			free (var->env->content);
			var->env->content = ft_strjoin("SH"
					"LVL=", temp3);
			free (temp2);
			free (temp3);
			var->env = temp;
			return ;
		}
		else
			var->env = var->env->next;
	}
	var->env = temp;
	return ;
}

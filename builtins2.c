#include "minishell.h"

void	ft_env(t_var *var)
{
	t_list	*temp;

	temp = var->env;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}

void	print_declare_x(t_var *var)
{
	char	*stock;
	t_list	*temp;
	int		i;

	i = -1;
	while (var->export)
	{
		temp = var->export->next;
		stock = ft_strdup((char *)var->export->content);
		printf("declare -x ");
		while (stock[++i] != '=')
			printf("%c", stock[i]);
		printf("=\"%s\"\n", ft_strchr(stock + i, '=') + 1);
		i = -1;
		free (stock);
		stock = NULL;
		free(var->export->content);
		free (var->export);
		var->export = temp;
	}

}

void	sort_export(t_list	**lst, char *env)
{
	t_list	*temp;

	temp = *lst;
	if (ft_strcmp(env, (char *)(*lst)->content) < 0)
		ft_lstadd_front(lst, ft_lstnew(ft_strdup(env)));
	else
	{
		while (temp->next && temp->next->next && 
				ft_strcmp(env,(char *)temp->next->content) > 0)
			temp = temp->next;
		if (temp->next && ft_strcmp(env,
				(char *)temp->next->content) < 0)
			ft_lstadd_next(&temp, ft_lstnew(ft_strdup(env)));
		else
			ft_lstadd_back(&temp, ft_lstnew(ft_strdup(env)));
	}
}

t_list	*print_export(t_var *var)
{
	t_list	*temp1;

	temp1 = var->env;
	var->export = ft_lstnew(ft_strdup((char *)var->env->content));
	var->env = var->env->next;
	while (var->env)
	{
		sort_export(&var->export, var->env->content);
		var->env = var->env->next;
	}
	var->env = temp1;
	return (print_declare_x(var), var->export);
}

void	ft_error_var_env(char **tab)
{
	ft_putstr_fd(tab[0], 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(tab[1], 2);
	return (ft_putstr_fd("': not a valid identifier\n", 2));
}


void	add_var_env(t_var *var, char **tab)
{
	int	i;

	i = 1;
	if (ft_isalpha(tab[1][0] == 0) && tab[1][0] != '_')
		ft_error_var_env(tab);
	while (tab[1] && tab[1][i] != '=' && (ft_isalnum(tab[1][i]) == 1 || tab[1][i] == '_'))
		i++;
	if (tab[1][i] != '=')
		ft_error_var_env(tab);
	else
		ft_lstadd_back(&var->env, ft_lstnew(ft_strdup(tab[1])));
}

void	ft_export(t_var *var, char **tab)
{
	if (!tab[1])
		print_export(var);
	else
		add_var_env(var, tab);
}

void	ft_cmd(t_var *var, char **tab)
{
	if (ft_strcmp(tab[0], "echo") == 0)
		ft_echo(tab);
	else if (ft_strcmp(tab[0], "pwd") == 0)
		ft_pwd(var, tab);
	else if (ft_strcmp(tab[0], "cd") == 0)
		ft_cd(var, tab);
	else if (ft_strcmp(tab[0], "export") == 0)
		ft_export(var, tab);
	else if (ft_strcmp(tab[0], "env") == 0)
		ft_env(var);
	// if (ft_strcmp(tab[0], "exit") == 0)
	// 	return (ft_exit());
	// if (ft_strcmp(tab[0], "unset") == 0)
	// 	return (ft_unset());
	else
		exec_pid(var, tab);
	return ;
}

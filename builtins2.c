#include "minishell.h"

void	ft_env(t_var *var)
{
	t_list	*temp;

	temp = var->updt_env;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}

t_list	*add_begin_export(t_var *var, t_list *temp)
{
	if (ft_strcmp((char *)var->updt_env->content,
		(char *)var->export->content) < 0)
	{
		ft_lstadd_front(&var->export, ft_lstnew(var->updt_env->content));
		temp = var->export;
		var->check_export = 1;
	}
	return (temp);
}

void	print_declare_x(t_var *var)
{
	while (var->export)
	{
		printf("declare -x %s\n", (char *)var->export->content);
		var->export = var->export->next;
	}
}

t_list	*print_export(t_var *var)
{
	t_list	*temp;

	var->export = ft_lstnew(var->updt_env->content);
	var->updt_env = var->updt_env->next;
	temp = var->export;
	while (var->updt_env)
	{
		temp = add_begin_export(var, temp);
		if (var->check_export != 1)
		{
			while (var->export->next->next && 
				ft_strcmp((char *)var->updt_env->content,
			(char *)var->export->next->content)	> 0)
				var->export = var->export->next;
			if (ft_strcmp((char *)var->updt_env->content,
					(char *)var->export->next->content) < 0)
				ft_lstadd_next(var->export, ft_lstnew(var->updt_env->content));
			else
				ft_lstadd_back(&var->export, ft_lstnew(var->updt_env->content));
			var->export = temp;
		}
		var->updt_env = var->updt_env->next;
		var->check_export = 0;
	}
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
	// pour l instant que : export test3=3
	//  a voir par la suite si on dot gerer : test2=2 puis export test2

	// export newtest="new"  si je fais ensuite export $newtest=bonjour :
	// 	declare -x new="bonjour"
	// declare -x newtest="new"
	if (ft_isalpha(tab[1][0] == 0) && tab[1][0] != '_')
		ft_error_var_env(tab);
	while (tab[1] && tab[1][i] != '=' && (ft_isalnum(tab[1][i]) == 1 || tab[1][i] == '_'))
		i++;
	if (tab[1][i] != '=')
		ft_error_var_env(tab);
	else
		ft_lstadd_back(&var->updt_env, ft_lstnew(tab[1]));
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
		ft_pwd();
	else if (ft_strcmp(tab[0], "cd") == 0)
		ft_cd(tab);
	else if (ft_strcmp(tab[0], "export") == 0)
		ft_export(var, tab);
	else if (ft_strcmp(tab[0], "env") == 0)
		ft_env(var);
	// if (ft_strcmp(tab[0], "exit") == 0)
	// 	return (ft_exit());
	// if (ft_strcmp(tab[0], "unset") == 0)
	// 	return (ft_unset());
	else
		ft_exe(var, tab);
	return ;
}


// void	ft_cmd(t_var *var, char **tab)
// {
// 	if (ft_strcmp(tab[0], "echo") == 0)
// 		return (ft_echo(tab));
// 	if (ft_strcmp(tab[0], "pwd") == 0)
// 		return (ft_pwd());
// 	if (ft_strcmp(tab[0], "cd") == 0)
// 		return (ft_cd(tab));
// 	if (ft_strcmp(tab[0], "export") == 0)
// 		return (ft_export(var, tab));
// 	if (ft_strcmp(tab[0], "env") == 0)
// 		return (ft_env(var));
// 	// if (ft_strcmp(tab[0], "exit") == 0)
// 	// 	return (ft_exit());
// 	// if (ft_strcmp(tab[0], "unset") == 0)
// 	// 	return (ft_unset());
// 	else
// 		return (ft_exe());
// }
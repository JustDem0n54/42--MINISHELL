#include "../../minishell.h"

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


void	ft_env(t_var *var, char **tab)
{
	t_list	*temp;

	(void)tab;
	temp = var->env;
	while (temp)
	{
		if (ft_strlen(ft_strchr((char *)temp->content, '=')) != 1)
			printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}


#include "../../minishell.h"

void	ft_env(t_var *var, char **tab)
{
	t_list	*temp;

	(void)tab;
	temp = var->env;
	while (temp)
	{
		if ((ft_strchr((char *)temp->content, '=')) != NULL)
			printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	var->status = 0;
}

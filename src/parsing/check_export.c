#include "../../minishell.h"

char	*check_export(t_var *var, char *str, int size)
{
	char	*newstr;
	t_list	*temp;

	newstr = NULL;
	temp = var->env;
	if (strcmp(str, "$?") == 0)
		return (ft_itoa(var->status));
	while (temp)
	{
		if (ft_strncmp((char *)temp->content, str, size) == 0)
		{
			newstr = ft_strdup(ft_strchr((char *)temp->content, '=') + 1);
			if (ft_strlen(newstr) == 0)
			{
				newstr = ft_strdup("");
			}
			break ;
		}
		else
			temp = temp->next;
	}
	return (newstr);
}

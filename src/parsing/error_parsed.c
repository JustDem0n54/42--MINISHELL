#include "../../minishell.h"

void	check_error_parsed(t_list *check)
{
	t_list	*temp;

	temp = check;
	while (temp && temp->next)
	{
		if (ft_strcmp((char *)temp->content, "|") == 0)
		{
			if (ft_strcmp((char *)temp->next->content, "|") == 0)
				return(ft_putstr_fd("Brioshell: syntax error near unexpected token `|'", 2));
		}
		temp = temp->next;
	}
}

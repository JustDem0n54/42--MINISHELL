#include "../../minishell.h"

int	check_error_parsed(t_list *check)
{
	t_list	*temp;

	temp = check;
	while (temp)
	{
		if (ft_strcmp((char *)temp->content, "|") == 0)
		{
			if (temp->next && ft_strcmp((char *)temp->next->content, "|") == 0)
				return(ft_putstr_fd("Brioshell: syntax error near unexpected token `|'\n", 2), 1);
			if (temp->next == NULL)
				return(ft_putstr_fd("Brioshell: syntax error near unexpected token `|'\n", 2), 1);
		}
		if (ft_strcmp((char *)temp->content, "<") == 0)
		{
			if (temp->next && ft_strcmp((char *)temp->next->content, "<") == 0)
				return(ft_putstr_fd("Brioshell: syntax error near unexpected token `newline'\n", 2), 1);
			if (temp->next == NULL)
				return(ft_putstr_fd("Brioshell: syntax error near unexpected token `<'\n", 2), 1);
		}
		if (ft_strcmp((char *)temp->content, ">") == 0)
		{
			if (temp->next && ft_strcmp((char *)temp->next->content, ">") == 0)
				return(ft_putstr_fd("Brioshell: syntax error near unexpected token `newline'\n", 2), 1);
			if (temp->next == NULL)
				return(ft_putstr_fd("Brioshell: syntax error near unexpected token `>'\n", 2), 1);
		}
		temp = temp->next;
	}
	return (0);
}

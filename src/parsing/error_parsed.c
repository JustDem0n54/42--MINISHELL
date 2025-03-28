#include "../../minishell.h"

int error_pipe(t_list *temp)
{
	if (ft_strcmp((char *)temp->content, "|") == 0)
	{
		if (temp->next && ft_strcmp((char *)temp->next->content, "|") == 0)
			return(ft_putstr_fd("Brioshell: syntax error"
			" near unexpected token `|'\n", 2), 1);
		if (temp->next == NULL)
			return(ft_putstr_fd("Brioshell: syntax error"
			" near unexpected token `|'\n", 2), 1);
	}
	return (0);
}

int error_infile(t_list *temp)
{
	if (ft_strcmp((char *)temp->content, "<") == 0)
	{
		if (temp->next && ft_strcmp((char *)temp->next->content, "<") == 0)
			return(ft_putstr_fd("Brioshell: syntax error near"
			" unexpected token `newline'\n", 2), 1);
		if (temp->next == NULL)
			return(ft_putstr_fd("Brioshell: syntax error near"
			" unexpected token `<'\n", 2), 1);
	}
	return (0);
}

int error_outfile(t_list *temp)
{
	if (ft_strcmp((char *)temp->content, ">") == 0)
	{
		if (temp->next && ft_strcmp((char *)temp->next->content, ">") == 0)
			return(ft_putstr_fd("Brioshell: syntax error near "
			"unexpected token `newline'\n", 2), 1);
		if (temp->next == NULL)
			return(ft_putstr_fd("Brioshell: syntax error near "
			"unexpected token `>'\n", 2), 1);
	}
	return (0);
}

int	check_error_parsed(t_list *check)
{
	t_list	*temp;

	temp = check;
	while (temp)
	{
		if (error_pipe(temp) == 1)
			return (1);
		if (error_infile(temp) == 1)
			return (1);
		if (error_outfile(temp) == 1)
			return (1);
		temp = temp->next;
	}
	return (0);
}

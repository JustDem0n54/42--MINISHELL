#include "minishell.h"

void	ft_lstadd_next(t_list *lst, t_list *new)
{
	t_list	*temp;

	if (new == NULL)
		return ;
	if (lst == NULL)
	{
		lst = new;
		return ;
	}
	temp = lst->next;
	lst->next = new;
	new->next = temp;
}

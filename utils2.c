#include "minishell.h"

void	ft_lstadd_next(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (new == NULL)
		return ;
	if ((*lst) == NULL)
	{
		(*lst) = new;
		return ;
	}
	temp = (*lst)->next;
	(*lst)->next = new;
	new->next = temp;
}

void	print_lst(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	printf("\nfin de la liste\n");
	return ;
}

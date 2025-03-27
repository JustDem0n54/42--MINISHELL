#include "../../minishell.h"

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

// void	print_lst(t_list *lst)
// {
// 	t_list	*temp;

// 	temp = lst;
// 	while (temp)
// 	{
// 		printf("%s$\n", (char *)temp->content);
// 		temp = temp->next;
// 	}
// 	printf("fin de la liste\n");
// 	return ;
// }

long int	ft_atol(char *str)
{
	long int	i;
	long int	res;
	int	n;

	res = 0;
	n = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n = -n;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (n * res);
}

size_t	ft_strlenlongint(long n)
{
	long	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n / 10 >= 1)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_litoa(long int nb)
{
	int		len;
	char	*str;

	len = ft_strlenlongint(nb);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (nb == 0)
		str[0] = 48;
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	str[len] = '\0';
	while (nb > 0)
	{
		str[len - 1] = nb % 10 + 48;
		nb = nb / 10;
		len--;
	}
	return (str);
}

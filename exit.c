#include "minishell.h"

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

void	ft_free_all(t_var *var)
{
	if (var->env != NULL)
		ft_lstclear(&(var->env), free);
	if (var->parse != NULL)
		ft_lstclear(&(var->parse), free);
	if (var->pwd != NULL)
		free (var->pwd);
	if (var->oldpwd != NULL)
		free (var->oldpwd);
	if (var->home != NULL)
		free (var->home);
	if (var->data != NULL)
		free_split(var->data);
	free(var);
	rl_clear_history();
}

void	ft_exit(t_var *var, char **tab)
{
	printf("exit\n");
	if (tab[1] && ft_strcmp(ft_litoa(ft_atol(tab[1])), tab[1]) != 0)
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(tab[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("numeric argument required\n", 2);
		ft_free_all(var);
		exit(2);
	}
	else if (tab[1] && tab[2])
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		// var->status = 127;
		return ;
	}
	else
	{
		ft_free_all(var);
		// if (tab[1][0] == '-')
		exit (ft_atol(tab[1]) % 256);
		exit(EXIT_SUCCESS);
	}
}
// exit 8 "" doit renvoyer too many argument 

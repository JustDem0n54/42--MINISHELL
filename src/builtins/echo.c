#include "../../minishell.h"


void	print_echo(t_var *var, char **tab, int i, int j)
{
	if (tab[i][j] == '~')
		ft_putstr_fd(var->home +5, 1);
	else if (tab[i] && tab[i][j])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(" ");
	}
}

void	ft_echo(t_var *var, char **tab)
{
	int	i;
	int	j;
	int	check;

	(void) var;
	i = 0;
	j = 0;
	check = 0;
	while (tab[++i])
	{
		if (tab[i][0] == '-' && tab[i][1] == 'n')
		{
			j = 1;
			while (tab[i][j] && tab[i][j] == 'n')
				j++;
			if (tab[i][j] == 0)
				check = 1;
		}
		print_echo(var, tab, i, j);
		j = 0;
	}
	if (check != 1)
		printf("\n");
}

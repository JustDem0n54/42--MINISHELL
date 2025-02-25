#include "minishell.h"

// echo "$PATH" = affiche le chemin
// echo '$PATH' = $PATH

//  echo "'bonjour'"
// 'bonjour'

// echo 'bonjour'
// bonjour

//  echo '"bonjour"'
// "bonjour"

// echo "[texte] $([commande])"

// edelanno@c2r3p3:~/42--MINISHELL$ echo "voici le cntenu du dossier $(ls)"
// voici le cntenu du dossier builtins.c
// Makefile
// minishell.h
// parsing.c
// README.md

// edelanno@c2r3p3:~/42--MINISHELL$ echo voici le cntenu du dossier $(ls)
// voici le cntenu du dossier builtins.c Makefile minishell.h parsing.c README.md


void	ft_echo(char **tab)
{
	int	i;
	int	check;

	i = 1;/*car tab 0 = commande echo*/
	check = 0; 
	// tab = ft_quote --> pour enlver les quotes a enlever
	if (ft_strncmp(tab[1], "-n", 2) == 0)
	{
		check = 1;
		i++;
	}
	while (tab[i])
	{
		printf("%s", tab[i]);
		i++;
	}
	if (check != 1)
		printf("\n");
}

void	ft_pwd(void)
{
	char	path[1024];

	int	i;

	i = 2;
	if (getcwd(path, sizeof(path)) != 0)
		printf("%s\n", path);
	else
	{
		while (sizeof(path) != 4096 || i < 5)
		{
			if (getcwd(path, i * sizeof(path)) != 0)
			{
				printf("%s\n", path);
				break ;
			}
			else
				i++;
		}
		if (getcwd(path, i * sizeof(path)) == 0)
			perror("getcwd");
	}
}




void	ft_cd(char **tab)
{
	
}
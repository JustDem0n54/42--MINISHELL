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
	if (ft_strcmp(tab[i], "-n") == 0)
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

void	ft_pwd(t_var *var, char **tab)
{
	char	path[1024];
	int	i;

	i = 1;
	if (getcwd(path, i * sizeof(path)) == 0)
	{
		while (sizeof(path) <= 4096)
		{
			if (getcwd(path, i * sizeof(path)) != 0)
				break ;
			else
				i++;
		}
	}
	if (getcwd(path, i * sizeof(path)) != 0 && ft_strcmp(tab[0], "pwd") == 0)
		printf("%s\n", path);
	else if (getcwd(path, i * sizeof(path)) == 0)
		perror("getcwd");/*voir pour le debut du message d erreur i/o getcwd*/
	var->previous_cd = path;
}

void	ft_cd(t_var *var, char **tab)
{

	(void) var;
	// var->previous_cd = ;
	if (chdir(tab[1]) == 0)
		ft_pwd(); /*pour check chemin, voir comment y aller dans le terminal*/
	else
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": ", 2);
		perror(tab[1]);
	}
}

t_list	*init_env(char **env) 
{
	int		i;
	t_list	*lst_env;

	i = 0;
	lst_env = NULL;
	while (env[i])
	{
		ft_lstadd_back(&lst_env, ft_lstnew(env[i]));
		i++;
	}
	return (lst_env);
}

void	ft_env(t_var *var)
{
	t_list	*new_env;

	new_env = var->lst_env;
	
	// while (new_env)
	// {
	// 	printf("%s\n", (char *)new_env->content);
	// 	new_env = new_env->next;
	// }
}



t_var	*init_struct(t_var *var, char **env)
{
	var = malloc(sizeof(t_list));
	if (!var)
		return NULL;
	var->lst_env = init_env(env);
	var->previous_cd = NULL;
	return (var);
	// ne pas oublier de free var->lst_env et var
}


int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;

	// char	*tab[]={"cd", "."};
	t_var	*var;

	var = NULL;
	var = init_struct(var, env);

	ft_pwd();
	// ft_cd(var, tab);
	// ft_env(var);
	

	// while (1)
	// {
	// 	line = readline("minishell>");
	// 	if (ft_strncmp(line, "fin", 3) == 0)
	// 		exit(0);
	// }
	return (0);
}

// export :
// ne peux pas commencer pas un chiffre ? sinon aue lettres / chiffres et _
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
	// voir pour check option
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
	// printf("prev dans pwd avant %s", (char *)var->previous_cd->content);
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
	if (getcwd(path, i * sizeof(path)) != 0)
	{	
		if (var->previous_cd)
		{
			printf("dans != null");
			// ft_lstclear(&var->previous_cd, free); /*PB DE FREE"
		}
		var->previous_cd = ft_lstnew(path);
		if (ft_strcmp(tab[0], "pwd") == 0)
			printf("%s\n", path);
	}
	else if (getcwd(path, i * sizeof(path)) == 0)
		perror("getcwd");/*voir pour le debut du message d erreur i/o getcwd*/
	// ne pas oublier de free var->previous_cd a la fin 
}

void	ft_cd(t_var *var, char **tab)
{
	(void) var;

	ft_pwd(var, tab);
	// printf("prev dans cd = %s\n", (char *)var->previous_cd->content);
	if (tab[2])
	{
		// perror(tab[0]);
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return;
	}
	if (ft_strcmp(tab[1], "~") == 0)
		tab[1] = ft_strdup((char *)var->previous_cd->content);
	// ft_pwd(var, tab); /*pour check*/
	if (chdir(tab[1]) != 0)
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": ", 2);
		perror(tab[1]);
	}
	ft_pwd(var, tab); /*pour check*/
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

	char	*tab[]={"pwd", "bonjour", "aure", NULL};
	t_var	*var;

	var = NULL;
	var = init_struct(var, env);

	ft_pwd(var, tab);
	ft_cd(var, tab);
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
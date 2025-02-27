#include "minishell.h"


// TEST 


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



// edelanno@c2r3p3:~/42--MINISHELL$ "$(ls)"
// bonjour
// builtins.c
// libft
// main.c
// Makefile
// minishell
// minishell.h
// obj
// parsing.c
// README.md: command not found
// edelanno@c2r3p3:~/42--MINISHELL$ $(ls)
// bonjour: command not found
// edelanno@c2r3p3:~/42--MINISHELL$ ls
// bonjour  builtins.c  libft  main.c  Makefile  minishell  minishell.h  obj  parsing.c  README.md
// edelanno@c2r3p3:~/42--MINISHELL$ 


// echo -n -n
//   434  echo -n n
//   435  echo -n -n
//   436  echo -n -n n
//   437  echo -n "-n"
//   438  echo -n '-n'
//   439  echo -n -e
//   440  echo -n -n -n -n -n -n -n 
//   441  echo -n -n -n -n -n -n -n bonj
//   442  echo -n -e -e -e -n


// edelanno@c2r3p3:/home$ echo "'-n'"
// '-n'
// edelanno@c2r3p3:/home$ echo '-n'
// edelanno@c2r3p3:/home$ 


// FIN DE TEST

void	ft_echo(char **tab)
{
	int	i;
	int	check;

	i = 1;
	check = 0;  
	// voir pour check option et -n-n-n
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

void	ft_pwd()
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
	if (getcwd(path, i * sizeof(path)) != 0)
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	else if (getcwd(path, i * sizeof(path)) == 0)
		perror("getcwd");/*voir pour le debut du message d erreur i/o getcwd*/

	// ne pas oublier de free var->pwd_history a la fin 
}

int	cd_specific_arg(char **tab)
{
	int	to_free;

	to_free = 0;
	if (ft_strcmp(tab[1], "-") == 0)
	{
		tab[1] = ft_strdup(getenv("OLDPWD")); /*pour le moment old pwd ne change pas, a voir si dans minishell ca change*/
		to_free = 1;
	}
	else if (ft_strcmp(tab[1], "~") == 0)
	{
		tab[1] = ft_strdup(getenv("HOME")); /*voir si home change ou !home*/
		to_free = 1;
	}
	return (to_free);

	/*voir avec les options que faire*/
}

void	ft_cd(char **tab)
{
	int	check;

	check = 0;
	if (tab[2])
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return;
	}
	if (!tab[1])
	{		
		if (chdir(getenv("HOME")) != 0) /*voir si !home ou si home est renomme*/
			perror(tab[0]);
	}
	else if (cd_specific_arg(tab) == 1)
		check = 1;
	// ft_pwd(var, tab); /*pour check*/
	if (chdir(tab[1]) != 0)
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": ", 2);
		perror(tab[1]);
	}
	if (check == 1)
		free(tab[1]);
	ft_pwd(); /*pour check*/
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
	var->pwd_history = NULL;
	return (var);
	// ne pas oublier de free var->lst_env et var
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;

	char	*tab[]={"cd", "bonjour", NULL};
	char	*tab1[]={"cd", "~", NULL};
	// char	*tab2[]={"cd", "-", NULL};
	t_var	*var;

	var = NULL;
	var = init_struct(var, env);

	// ft_pwd();
	ft_cd(tab);
	ft_cd(tab1);
	// ft_cd(tab2);
	// printf("%s\n", getenv("PATH"));
	
	// ft_env(var);
	
	return (0);
}

// export :
// trier et faire declare x 
// ne peux pas commencer pas un chiffre ? sinon aue lettres / chiffres et _




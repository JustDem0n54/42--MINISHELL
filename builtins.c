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
// echo -n -n -n -n -n -n -n 
// echo -n "-n"
// echo -n '-n'
// echo -n -e -e -e -n
// = rien 

// echo -n n 
// echo -n -n n
// = n (sans \n)

//  echo "'-n'"
// = '-n'

// echo -n -n -n -n -n -n -n bonj = bonj (sans \n)

// edelanno@c2r3p3:~$ "
// > "^C
// edelanno@c2r3p3:~$ +
// +: command not found
// edelanno@c2r3p3:~$ _!
// _!: command not found
// edelanno@c2r3p3:~$ @
// @: command not found
// edelanno@c2r3p3:~$ #
// edelanno@c2r3p3:~$ $
// $: command not found
// edelanno@c2r3p3:~$ %
// bash: fg: %: no such job
// edelanno@c2r3p3:~$ ^
// bash: :s^: no previous substitution
// edelanno@c2r3p3:~$ &
// bash: syntax error near unexpected token `&'
// edelanno@c2r3p3:~$ *
// 42--MINISHELL: command not found
// edelanno@c2r3p3:~$ (
// > ^C


// FIN DE TEST

// a completer avec les conditions stdin / stdout / return value 

void	ft_echo(char **tab)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	while (tab[i] && ft_strcmp(tab[i], "-n") == 0)
	{
		check = 1;
		i++;
	}
	while (tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(" ");
		i++;
	}
	if (check != 1)
		printf("\n");
}

void	ft_pwd(void)
{
	char	path[1024];
	int		i;

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
}

int	cd_specific_arg(char **tab)
{
	if (ft_strcmp(tab[1], "-") == 0)
		tab[1] = ft_strdup(getenv("OLDPWD")); /*pour le moment old pwd ne change pas, a voir si dans minishell ca change*/
	else if (ft_strcmp(tab[1], "~") == 0)
		tab[1] = ft_strdup(getenv("HOME")); /*voir si home change ou !home*/
	if (tab[1] == NULL)
		return (-1);
	return (0);
}


// void	update_env(t_var *var)
// {
// 	t_list	*temp;

// 	temp = var->updt_env;
// 	while (var->updt_env)
// 	{
// 		if (ft_strncmp((char *)var->updt_env->content, "PWD", 3) == 0)
// 			var->updt_env->content = ft_strdup(ft_pwd)
// 	}
// }

// void	update_pwd_env(t_var *var)
// {
// 	t_list	*temp;

// 	temp = var->updt_env;
// 	while (var->updt_env)
// 	{
// 		if (ft_strncmp((char *)var->updt_env->content, "PWD", 3) == 0)
// 			var->updt_env->content = ft_strdup(getenv)
// 	}
// }

int	ft_cd(char **tab)
{

	if (tab[2])
		return (ft_putstr_fd(tab[0], 2), ft_putstr_fd(": too many arguments\n", 2), 1);
	if (!tab[1])
	{		
		if (chdir(getenv("HOME")) != 0) /*voir si !home ou si home est renomme*/
			perror(tab[0]); /*perror ok ? man = STDERR The standard error shall be used only for diagnostic messages.*/
	}
	else if (cd_specific_arg(tab) == -1)
		return (1);
	// ft_pwd(var, tab); /*pour check*/
	if (chdir(tab[1]) != 0)
		return (ft_putstr_fd(tab[0], 2), ft_putstr_fd(": ", 2), perror(tab[1]), 1);
	// ft_pwd(); /*pour check*/
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)	argc;
	(void)	argv;
	char	*tab[]={"export", NULL};
	t_var	var;

	init_struct(&var, env);
	ft_cmd(&var, tab);
	ft_lstclear(&var.updt_env, free);
	ft_lstclear(&var.export, free);
	return (0);
}


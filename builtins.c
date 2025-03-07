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

char	*ft_pwd(char **tab)
{
	char	path[1024];
	char	*stock_path;
	int		i;

	i = 1;
	stock_path = NULL;
	while (sizeof(path) <= 4096 && getcwd(path, i * sizeof(path)) == 0)
	{
		if (getcwd(path, i * sizeof(path)) != 0)
			break ;
		else
			i++;
	}
	if (ft_strcmp(tab[0], "pwd") == 0 && getcwd(path, i * sizeof(path)) != 0)
		printf("%s\n", path);
	else if (getcwd(path, i * sizeof(path)) == 0)
		perror("pwd");/*voir pour le debut du message d erreur*/
	if (ft_strcmp(tab[0], "cd") == 0)
		stock_path = ft_strdup(path);
	return(stock_path);
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
	// char	*stock_path;
	// printf("home = %s\n",getenv("HOME"));
	// printf("old = %s\n",getenv("OLDPWD"));
	// printf("pwd = %s\n",getenv("PWD"));
	// ft_pwd();
	// printf("\n\n");
	
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
	// printf("home = %s\n", getenv("HOME"));
	// printf("old = %s\n", getenv("OLDPWD"));
	// printf("pwd = %s\n", getenv("PWD"));
	// ft_pwd();
	// printf("\n");
	// ft_pwd(); /*pour check*/
	return (0);
}



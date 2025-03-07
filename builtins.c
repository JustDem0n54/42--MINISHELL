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

void	ft_echo(t_var *var, char **tab)
{
	int	i;
	int	check;

	(void)var;
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

// char	*update_pwd_env(t_var *var)
// {
// 	char	*old_pwd;

// 	old_pwd = ft_strdup((char *)var->env->content);
// 	free (var->env->content);
// 	var->env->content = ft_strdup((char *)var->stock_pwd);
// 	printf("new pwd = %s\n", (char *)var->env->content);
// 	return (old_pwd);

// }

// void	update_oldpwd_env(t_var *var, t_list *stock_oldpwd, char *new_oldpwd)
// {
// 	var->env = stock_oldpwd;
// 	free (var->env->content);
// 	printf("new oldpwd = %s\n", (char *)new_oldpwd);
// 	var->env->content = ft_strjoin("OLD", ((char *)new_oldpwd));
// 	printf("new oldpwd dans env= %s\n", (char *)var->env->content);
// 	if (new_oldpwd)
// 		free (new_oldpwd);
// }

// void	update_env(t_var *var, char *to_modify)
// {
// 	t_list	*temp;
// 	char	*new_env;

// 	temp = var->env;
// 	new_env = NULL;
// 	// ft_pwd(var, tab);
// 	while (var->env)
// 	{
// 		if (ft_strncmp((char *)var->env->content, to_modify, ft_strlen(to_modify)) == 0)
// 		{
// 			new_env = ft_strdup((char *)var->env->content);
// 			free (var->env->content);
// 			var->env->content = ft_strdup((char *)var->stock_pwd);
// 			printf("new pwd = %s\n", (char *)var->env->content);
// 		}

// 	var->env = var->env->next;		
// 	}
// 	update_oldpwd_env(var, stock_oldpwd, new_oldpwd);
// 	var->env = temp;
// 	return ;
// }



// HOME 
// SHLVL
// 	}

void	ft_pwd(t_var *var, char **tab)
{
	char	path[1024];
	int		i;

	i = 1;
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
	if (var->pwd != NULL)
		free (var->pwd);
	var->pwd = ft_strjoin("PWD=", path);
	return ;
}

void	update_env_pwd_and_old_(t_var *var)
{
	t_list	*temp;

	temp = var->env;
	while (var->env)
	{
		if (ft_strncmp((char *)var->env->content, "PWD=", 4) == 0)
		{
			free (var->env->content);
			var->env->content = ft_strdup((char *)var->pwd);
		}
		else if (ft_strncmp((char *)var->env->content, "OLDPWD=", 7) == 0)
		{
			free (var->env->content);
			var->env->content = ft_strdup((char *)var->oldpwd);
		}
	var->env = var->env->next;		
	}
	var->env = temp;
	return ;
}

int	cd_specific_arg(t_var *var, char **tab)
{
	if (ft_strcmp(tab[1], "-") == 0)
		tab[1] = ft_strdup(var->oldpwd + 7); /*pour le moment old pwd ne change pas, a voir si dans minishell ca change*/
	else if (ft_strcmp(tab[1], "~") == 0)
		tab[1] = ft_strdup(getenv("HOME")); /*voir si home change ou !home*/
	if (tab[1] == NULL)
		return (-1);
	return (0);
}

int	ft_cd(t_var *var, char **tab)
{
	if (tab[1] && tab[2])
		return (ft_putstr_fd(tab[0], 2), ft_putstr_fd(": too many arguments\n", 2), 1);
	if (!tab[1])
	{	
		if (chdir(getenv("HOME")) != 0) /*voir si !home ou si home est renomme*/
		{
			return (perror(tab[0]), 1); /*perror ok ? man = STDERR The standard error shall be used only for diagnostic messages.*/
		}
	}
	else if (cd_specific_arg(var, tab) == -1)
		return (1);
	if (chdir(tab[1]) != 0)
		return (ft_putstr_fd(tab[0], 2), ft_putstr_fd(": ", 2), perror(tab[1]), 1);
	if (var->oldpwd != NULL)
		free (var->oldpwd);
	var->oldpwd = ft_strjoin("OLD", ft_strdup(var->pwd));
	ft_pwd(var, tab);
	update_env_pwd_and_old_(var);
	return (0);
}



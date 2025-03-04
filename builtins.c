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
}

int	ft_cd(char **tab)
{
	int	check;

	check = 0;
	if (tab[2])
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return (1);
	}
	if (!tab[1])
	{		
		if (chdir(getenv("HOME")) != 0) /*voir si !home ou si home est renomme*/
			perror(tab[0]); /*perror ok ? man = STDERR The standard error shall be used only for diagnostic messages.*/
	}
	else if (cd_specific_arg(tab) == 1)
		check = 1;
	// ft_pwd(var, tab); /*pour check*/
	if (chdir(tab[1]) != 0)
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": ", 2);
		return (perror(tab[1]), 1);
	}
	if (check == 1)
		free(tab[1]);
	// ft_pwd(); /*pour check*/
	return (0);
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
	return (var);
	// ne pas oublier de free var->lst_env et var
}

void	ft_lstadd_next(t_list *lst, t_list *new)
{
	t_list	*temp;

	if (new == NULL)
		return ;
	if (lst == NULL)
	{
		lst = new;
		return ;
	}
	temp = lst->next;
	lst->next = new;
	new->next = temp;
}

t_list	*ft_export(t_var *var)
{
	t_list	*lst_export;
	t_list	*temp;
	int		check;

	check = 0;
	lst_export = ft_lstnew(var->lst_env->content);
	var->lst_env = var->lst_env->next;	
	temp = lst_export;
	while (var->lst_env)
	{
		if (ft_strcmp((char *)var->lst_env->content, (char *)lst_export->content) < 0)
		{
			ft_lstadd_front(&lst_export, ft_lstnew(var->lst_env->content));
			temp = lst_export;
			check = 1;
		}
		if (check != 1)
		{
			while (lst_export->next->next && ft_strcmp((char *)var->lst_env->content, (char *)lst_export->next->content) > 0)
				lst_export = lst_export->next;
			if (ft_strcmp((char *)var->lst_env->content, (char *)lst_export->next->content) < 0)
				ft_lstadd_next(lst_export, ft_lstnew(var->lst_env->content));
			else
				ft_lstadd_back(&lst_export, ft_lstnew(var->lst_env->content));
			lst_export = temp;
		}
		var->lst_env = var->lst_env->next;
		check = 0;
	}
	while (lst_export)
	{
		printf("declare -x %s\n", (char *)lst_export->content);
		lst_export = lst_export->next;
	}
	return (lst_export);
}

void	add_var_env(char **tab)
{
	// pour l instant que : export test3=3
	//  a voir par la suite si on dot gerer : test2=2 puis export test2

	// export newtest="new"  si je fais ensuite export $newtest=bonjour :
	// 	declare -x new="bonjour"
	// declare -x newtest="new"
	if (!(tab[1][0] >= 'A' && tab[1][0] <= 'Z') && !(tab[1][0] >= 'a' && tab[1][0] <= 'z') && tab[1][0] != '_' )
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(tab[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		// return (perror(tab[1]));
	}
}


// =word / variable d environnement ne peux pas commencer pas un chiffre ? sinon aue lettres / chiffres et _

int	main(int argc, char **argv, char **env)
{
	(void)	argc;
	(void)	argv;
	// t_list	*export;


	// char	*tab[]={"cd", "bonjour", NULL};
	// char	str[]={"'-n'"};
	char	*tab1[]={"export", "8=8", NULL};
	// char	*tab2[]={"cd", "-", NULL};
	t_var	*var;

	var = NULL;
	var = init_struct(var, env);

	// ft_putstr_fd(str, 1);
	// ft_pwd();
	// ft_cd(tab);
	// ft_cd(tab1);
	// ft_cd(tab2);
	// export = ft_export(var);
	add_var_env(tab1);

	// while (export)
	// {
		// printf("export = %s\n", (char *)export->content);
		// printf("bon$$$ jourrr");
		// export = export->next;
	// }

	// printf("%s\n", getenv("PATH"));
	
	// ft_env(var);
	
	return (0);
}






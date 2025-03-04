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

t_var	*init_struct(t_var *var, char **env)
{
	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->init_env = init_env(env);
	var->updt_env = var->init_env;
	var->export = NULL;
	var->check_export = 0;
	return (var);
	// ne pas oublier de free var->updt_env et var
}




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

void	ft_env(t_var *var)
{
	t_list	*temp;

	temp = var->updt_env;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
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

t_list	*add_begin_export(t_var *var, t_list *temp)
{
	if (ft_strcmp((char *)var->updt_env->content, 
		(char *)var->export->content) < 0)
	{
		ft_lstadd_front(&var->export, ft_lstnew(var->updt_env->content));
		temp = var->export;
		var->check_export = 1;
	}
	return (temp);
}



void	print_declare_x(t_var *var)
{
	while (var->export)
	{
		printf("declare -x %s\n", (char *)var->export->content);
		var->export = var->export->next;
	}
}

t_list	*print_export(t_var *var)
{
	t_list	*temp;

	var->export = ft_lstnew(var->updt_env->content);
	var->updt_env = var->updt_env->next;
	temp = var->export;
	while (var->updt_env)
	{
		temp = add_begin_export(var, temp);
		if (var->check_export != 1)
		{
			while (var->export->next->next && 
				ft_strcmp((char *)var->updt_env->content,
			(char *)var->export->next->content)	> 0)
				var->export = var->export->next;
			if (ft_strcmp((char *)var->updt_env->content,
					(char *)var->export->next->content) < 0)
				ft_lstadd_next(var->export, ft_lstnew(var->updt_env->content));
			else
				ft_lstadd_back(&var->export, ft_lstnew(var->updt_env->content));
			var->export = temp;
		}
		var->updt_env = var->updt_env->next;
		var->check_export = 0;
	}
	return (print_declare_x(var), var->export);
}

void	ft_error_var_env(char **tab)
{
	ft_putstr_fd(tab[0], 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(tab[1], 2);
	return (ft_putstr_fd("': not a valid identifier\n", 2));
}


void	add_var_env(t_var *var, char **tab)
{
	int	i;

	i = 1;
	// pour l instant que : export test3=3
	//  a voir par la suite si on dot gerer : test2=2 puis export test2

	// export newtest="new"  si je fais ensuite export $newtest=bonjour :
	// 	declare -x new="bonjour"
	// declare -x newtest="new"
	if (ft_isalpha(tab[1][0] == 0) && tab[1][0] != '_')
		ft_error_var_env(tab);
	while (tab[1] && tab[1][i] != '=' && (ft_isalnum(tab[1][i]) == 1 || tab[1][i] == '_'))
		i++;
	if (tab[1][i] != '=')
		ft_error_var_env(tab);
	else
		ft_lstadd_back(&var->updt_env, ft_lstnew(tab[1]));
}

void	ft_export(t_var *var, char **tab)
{
	if (!tab[1])
		print_export(var);
	else
		add_var_env(var, tab);
}

// void	ft_cmd(t_var *var, char **tab)
// {
// 	if (ft_strcmp(tab[0], "echo") == 0)
// 		return (ft_echo(tab));
// 	if (ft_strcmp(tab[0], "pwd") == 0)
// 		return (ft_pwd());
// 	if (ft_strcmp(tab[0], "cd") == 0)
// 		return (ft_cd(tab));
// 	if (ft_strcmp(tab[0], "export") == 0)
// 		return (ft_export(var, tab));
// 	if (ft_strcmp(tab[0], "env") == 0)
// 		return (ft_env(var));
// 	// if (ft_strcmp(tab[0], "exit") == 0)
// 	// 	return (ft_exit());
// 	// if (ft_strcmp(tab[0], "unset") == 0)
// 	// 	return (ft_unset());
// 	else
// 		return (ft_exe());
// }

void	ft_cmd(t_var *var, char **tab)
{
	if (ft_strcmp(tab[0], "echo") == 0)
		ft_echo(tab);
	else if (ft_strcmp(tab[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(tab[0], "cd") == 0)
		ft_cd(tab);
	else if (ft_strcmp(tab[0], "export") == 0)
		ft_export(var, tab);
	else if (ft_strcmp(tab[0], "env") == 0)
		ft_env(var);
	// if (ft_strcmp(tab[0], "exit") == 0)
	// 	return (ft_exit());
	// if (ft_strcmp(tab[0], "unset") == 0)
	// 	return (ft_unset());
	else
		ft_exe(var, tab);
	return ;
}

int	main(int argc, char **argv, char **env)
{
	(void)	argc;
	(void)	argv;
	// t_list	*export;


	char	*tab[]={"ls", NULL};
	// char	str[]={"'-n'"};
	t_var	*var;

	var = NULL;
	var = init_struct(var, env);

	// printf("dans main %s\n", (char *)var->updt_env->content);
	// ft_putstr_fd(str, 1);
	// ft_env(var);
	// ft_cd(tab);
	// ft_cd(tab1);
	// ft_cd(tab2);
	// export = ft_export(var);
	// add_var_env(var, tab1);
	// printf("%d\n", ft_strcmp("-n", "-n"));
	ft_cmd(var, tab);

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






#include "minishell.h"


// TEST 


// echo "$PATH" = affiche le chemin
// echo '$PATH' = $PATH

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

void	print_echo(char **tab, int i)
{
	printf("%s", tab[i]);
	if (tab[i + 1])
		printf(" ");
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
			j = 1;
		while (tab[i][j] && tab[i][j] == 'n')
			j++;
		if (tab[i][j] == 0)
			check = 1;
		if (tab[i] && tab[i][j])
			print_echo(tab, i);
		j = 0;
	}
	if (check != 1)
		printf("\n");
}

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
		tab[1] = ft_strdup(var->oldpwd + 7);
	else if (ft_strcmp(tab[1], "~") == 0)
		tab[1] = ft_strdup(var->home + 5);
	if (tab[1] == NULL)
		return (-1);
	return (0);
}

void	ft_cd(t_var *var, char **tab)
{
	if (tab[1] && tab[2])
		return (ft_putstr_fd(tab[0], 2),
			ft_putstr_fd(": too many arguments\n", 2));
	if (!tab[1])
	{
		if (chdir(var->home + 5) != 0)
			return (perror(tab[0])); /*perror ok ? man = STDERR The standard error shall be used only for diagnostic messages.*/
		return ;
	}
	else if (cd_specific_arg(var, tab) == -1)
		return ;/*voir si return error*/
	if (chdir(tab[1]) != 0)
		return (ft_putstr_fd(tab[0], 2), ft_putstr_fd(": ", 2), perror(tab[1]));
	if (var->oldpwd != NULL)
		free (var->oldpwd);
	var->oldpwd = ft_strjoin("OLD", ft_strdup(var->pwd));
	ft_pwd(var, tab);
	update_env_pwd_and_old_(var);
	return ;
}

#include "../../minishell.h"

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

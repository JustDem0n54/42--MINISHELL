#include "../../minishell.h"

void	ft_pwd(t_var *var, char **tab)
{
	char	*path;
	
	path = getcwd(NULL, 0);
	if (ft_strcmp(tab[0], "pwd") == 0 && path != 0)
		printf("%s\n", path);
	else if (path == 0)
		perror("pwd");/*voir pour le debut du message d erreur*/
	if (var->pwd != NULL)
		free (var->pwd);
	var->pwd = ft_strjoin("PWD=", path);
	return ;
}

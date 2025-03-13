#include "../../minishell.h"

void	error_unset(char **tab)
{
	ft_putstr_fd(tab[0], 2);
	if (!tab[1])
		ft_putstr_fd(": HOME not set\n", 2);
	else if (ft_strcmp(tab[1], "-") == 0)
		ft_putstr_fd(": OLDPWD not set\n", 2);
	return ;
}

int	cd_specific_arg(t_var *var, char **tab)
{
	if (ft_strcmp(tab[1], "-") == 0)
	{
		if (!var->oldpwd)
			return (error_unset(tab), -1);
		tab[1] = ft_strdup(var->oldpwd + 7);
	}
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
		if (!var->home)
			return (error_unset(tab));
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

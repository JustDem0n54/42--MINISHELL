/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:43:20 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/02 13:43:21 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_var *var, char **tab)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (ft_strcmp(tab[0], "pwd") == 0 && path != 0)
		printf("%s\n", path);
	else if (path == 0)
		perror("error pwd");
	if (var->pwd != NULL)
		free (var->pwd);
	var->pwd = ft_strjoin("PWD=", path);
	var->status = 0;
	free(path);
	return ;
}

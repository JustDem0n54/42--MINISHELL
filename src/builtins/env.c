/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:43:07 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/02 13:43:08 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_var *var, char **tab)
{
	t_list	*temp;

	(void)tab;
	temp = var->env;
	while (temp)
	{
		if ((ft_strchr((char *)temp->content, '=')) != NULL)
			printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	var->status = 0;
}

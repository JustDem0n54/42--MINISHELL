/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollar2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:44:04 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/02 13:44:05 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pos_end_dollar_var(char *str, int *i)
{
	*i = *i + 1;
	while (ft_isalnum(str[*i]) == 1 || str[*i] == '_')
		*i = *i + 1;
	*i = *i - 1;
}

char	*dollar_value(t_var *var, char *str, int *i)
{
	char	*temp2;
	int		y;

	y = *i + 1;
	pos_end_dollar_var(str, i);
	temp2 = NULL;
	temp2 = check_export(var, str + y, *i - y + 1);
	return (temp2);
}

char	*join_str_dollar_value(char *temp, char *temp2, char *cpy)
{
	if (temp2 == NULL)
		cpy = temp;
	else if (temp != NULL)
	{
		cpy = ft_strnjoin(2, (char *[]){temp, temp2}, "");
		free(temp);
		free(temp2);
	}
	else
		cpy = temp2;
	return (cpy);
}

char	*only_dollar(char *temp, char *cpy)
{
	if (temp != NULL)
	{
		cpy = ft_strjoin(temp, "$");
		free (temp);
	}
	else
		cpy = ft_strdup("$");
	return (cpy);
}

char	*parse_dollar(t_var *var, char *str, int *i, int y)
{
	char	*temp;
	char	*cpy;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	cpy = NULL;
	if (*i > 0)
		temp = ft_substr(str, y, *i - y);
	if (ft_isdigit(str[*i + 1]) == 1 || str[*i + 1] == '?')
	{
		if (ft_isdigit(str[*i + 1]) == 1)
			cpy = temp;
		else if (str[*i + 1] == '?')
			cpy = check_return_value(var, temp);
		*i += 2;
	}
	else if (ft_isalpha(str[*i + 1]) == 1 || str[*i + 1] == '_')
	{
		temp2 = dollar_value(var, str, i);
		cpy = join_str_dollar_value(temp, temp2, cpy);
	}
	else
		cpy = only_dollar(temp, cpy);
	return (cpy);
}

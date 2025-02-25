/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:43:40 by nrontard          #+#    #+#             */
/*   Updated: 2025/02/07 14:46:39 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnjoinlen(int size, char **strs, char *sep)
{
	int	i;
	int	j;
	int	c;
	int	save;

	save = 0;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (strs[i][j])
		{
			j++;
			save++;
		}
		i++;
	}
	c = 0;
	while (sep[c])
		c++;
	return (save + ((size - 1) * c));
}

char	*ft_strjoincpy(char **strs, char *result, char *sep, int size)
{
	int	i;
	int	j;
	int	c;
	int	k;

	i = 0;
	c = 0;
	while (strs[i])
	{
		k = 0;
		j = 0;
		while (strs[i][j])
			result[c++] = strs[i][j++];
		if (i == size - 1)
		{
			result[c] = '\0';
			return (result);
		}
		while (sep[k])
			result[c++] = sep[k++];
		i++;
	}
	return (result);
}

char	*ft_strnjoin(int size, char **strs, char *sep)
{
	char	*result;
	int		size_max;

	if (size == 0)
	{
		result = malloc(sizeof(char));
		*result = 0;
		return (result);
	}
	size_max = ft_strnjoinlen(size, strs, sep);
	result = malloc((size_max + 1) * sizeof(char));
	return (ft_strjoincpy(strs, result, sep, size));
}

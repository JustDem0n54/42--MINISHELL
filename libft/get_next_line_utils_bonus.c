/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:24:08 by nrontard          #+#    #+#             */
/*   Updated: 2025/02/13 14:58:34 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_bzerognl(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	while (n > 0)
	{
		*str++ = 0;
		n--;
	}
}

void	*ft_callocgnl(size_t count, size_t size)
{
	void	*str;

	if (count == 0 || size == 0 || count * size / size != count)
		return (NULL);
	str = (void *)malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzerognl(str, count * size);
	return (str);
}

int	ft_strchrgnl(char *str, int c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlengnl(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

char	*ft_strjoingnl(char *storage, char *buff, int size)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	str = (char *)ft_callocgnl((ft_strlengnl(storage) + size + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	if (storage != NULL)
	{
		while (storage[i])
		{
			str[i] = storage[i];
			i++;
		}
	}
	j = -1;
	if (buff != NULL)
	{
		while (buff[++j])
			str[i + j] = buff[j];
	}
	str[(ft_strlengnl(storage) + size)] = '\0';
	return (str);
}

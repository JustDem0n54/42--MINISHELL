/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:08:47 by nrontard          #+#    #+#             */
/*   Updated: 2025/03/28 11:23:10 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// #include <stdio.h>

// int main(void)
// {
// 	printf("%zu\n", ft_strlen("Test"));
// 	printf("%zu\n", ft_strlen("Gros TeST !"));
// 	printf("%zu\n", ft_strlen(""));
// }
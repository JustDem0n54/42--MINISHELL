/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:49:51 by nrontard          #+#    #+#             */
/*   Updated: 2025/03/21 18:07:58 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*newstr;
	int		j;

	j = 0;
	newstr = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	while (str[j] != '\0')
	{
		newstr[j] = str[j];
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}

// int main(void)
// {
// 	printf("%s", ft_strdup("Hello"));
// 	return (0);
// }
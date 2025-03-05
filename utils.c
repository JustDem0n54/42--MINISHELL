#include "minishell.h"

char	*ft_strncpy(char *str, int size)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char) * (size + 1));
	while (i < size)
		dest[j++] = str[i++];
	dest[j] = 0;
	return (dest);
}
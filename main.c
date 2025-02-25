#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell>");
		if (ft_strncmp(line, "fin", 3) == 0)
			exit(0);
	}
	return (0);
}

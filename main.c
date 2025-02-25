#include "minishell.h"

char	*ft_read(char *argv)
{
	char	*line;

	line = readline(argv);
	return (line);
}

int main(int argc, char **argv)
{
	(void)	argc;
	(void)	argv;
	
	if (argc > 1)
		printf("argv 1 =%s\n", ft_read(argv[1]));
	return (0);
}
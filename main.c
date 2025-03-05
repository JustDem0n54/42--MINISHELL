#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_var	*var;
	int i = 0;

	(void) argc;
	(void) argv;
	(void) env;
	var = malloc(sizeof(t_var));
	while (1)
	{
		line = readline("minishell>");
		add_history(line);
		var->parse = parsing_line(line);
		var->data = convert_parse(var->parse);
		while (var->data[i] != NULL)
		{
			printf("%s=\n", var->data[i]);
			i++;
		}
		free_split(var->data);
		i = 0;
		if (ft_strncmp(line, "fin", 3) == 0)
		{
			ft_lstclear(&(var->parse), free);
			free(var);
			rl_clear_history();
			exit(0);
		}
	}
	return (0);
}

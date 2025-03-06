#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_var	*var;
	int i = 0;

	(void) argc;
	(void) argv;
	var = NULL;
	while (1)
	{
		line = readline("\033[1;33mBrioShell>\033[0m");
		if (ft_strncmp(line, "exit", 3) == 0)
		{
			// ft_lstclear(&(var->parse), free);
			// free(var);
			// rl_clear_history();
			return (0);
		}
		add_history(line);
		var = init_struct(var, env);
		var->parse = parsing_line(line);
		var->data = convert_parse(var->parse);
		ft_cmd(var, var->data);
		free_split(var->data);
		i = 0;
	}
	return (0);
}

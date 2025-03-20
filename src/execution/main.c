#include "../../minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_var	*var;
	(void) argc;
	(void) argv;

	var = NULL;
	var = init_struct(var, env);
	increase_shlvl(var);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, ft_ctrl_slash);
	while (1)
	{
		line = readline("\033[1;33mBrioShell>\033[0m");
		if (line == NULL)
			return (1);
		if (line != NULL && ft_strcmp(line, "") != 0)
		{
			add_history(line);
			var->parse = parsing_line(line);
			check_error_parsed(var->parse);
			var->data = convert_parse(var->parse);
			var->exec = init_exec(var, var->data);

			execution(var, var->exec);
			if (var->exec != NULL)
				ft_free_exec(var->exec);
			free(line);
			if (var->parse != NULL)
				ft_lstclear(&(var->parse), free);
			if (var->data != NULL)
				free_split(var->data);
		}
	}
	return (0);
}

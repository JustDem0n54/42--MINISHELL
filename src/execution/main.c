#include "../../minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_var	*var;
	int i = 0;
	(void) argc;
	(void) argv;

	var = NULL;
	var = init_struct(var, env);
	increase_shlvl(var);
	while (1)
	{
		line = readline("\033[1;33mBrioShell>\033[0m");
		if (line == NULL)
			return (1);
		if (line != NULL && ft_strcmp(line, "") != 0)
		{
			add_history(line);
			var->parse = parsing_line(line);
			var->data = convert_parse(var->parse);
			// if (var->parse != NULL)
			// 	ft_lstclear(&(var->parse), free);
			var->exec = init_exec(var, var->data);
			// if (var->data != NULL)
			// 	free_split(var->data);
			execution(var, var->exec);
		
			// free_split(exec->cmd);	
			// free(exec->path);
		}
		free(line);
		if (var->exec != NULL)
			ft_free_exec(var->exec);
		if (var->parse != NULL)
			ft_lstclear(&(var->parse), free);
		if (var->data != NULL)
			free_split(var->data);
		i = 0;
	}
	return (0);
}

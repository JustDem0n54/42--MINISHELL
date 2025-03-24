#include "../../minishell.h"

int	g_ctrl;

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
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		
		line = readline("\033[1;33mBrioShell>\033[0m");
		if (line == NULL)
		{
			free(line);
			ft_exit(var, (char *[]){NULL, NULL});
			return (1);
		}
		if (line != NULL && ft_strcmp(line, "") != 0)
		{
			add_history(line);
			var->parse = parsing_line(line);
			if (check_error_parsed(var->parse) == 0)
			{
				var->data = convert_parse(var, var->parse);
				var->exec = init_exec(var, var->data);
					
			}
			execution(var, var->exec);
			if (var->exec != NULL)
				ft_free_exec(var->exec);
			free(line);
			if (var->parse != NULL)
				ft_lstclear(&(var->parse), free);
			if (var->data != NULL)
				free_split(var->data);
			var->exec = NULL;
			var->parse = NULL;
			var->data = NULL;
			g_ctrl = 0;
		}
	}
	return (0);
}

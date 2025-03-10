#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_var	*var;
	int i = 0;
	(void) argc;
	(void) argv;

	var = NULL;
	var = init_struct(var, env);
	while (1)
	{
		line = readline("\033[1;33mBrioShell>\033[0m");
		if (line != NULL && ft_strcmp(line, "") != 0)
		{
			if (ft_strncmp(line, "exit", 3) == 0)
			{
				if (var->env != NULL)
					ft_lstclear(&(var->env), free);
				if (var->parse != NULL)
					ft_lstclear(&(var->parse), free);
				if (var->pwd != NULL)
					free (var->pwd);
				if (var->oldpwd != NULL)
					free (var->oldpwd);
				if (var->home != NULL)
					free (var->home);
				free(var);
				rl_clear_history();
				return (0);
			}
			add_history(line);
			var->parse = parsing_line(line);
			var->data = convert_parse(var->parse);
			execution(var, var->data);
			free_split(var->data);
		}
		free(line);
		i = 0;
	}
	return (0);
}

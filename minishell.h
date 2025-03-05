#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"


typedef	struct s_var
{
	t_list	*init_env;
	t_list	*updt_env;
	t_list	*export;
	t_list	*parse;
	int		check_export;
	
}	t_var;

t_list	*parsing_line(char *str);
void	ft_exe(t_var *var, char **tab);

#endif

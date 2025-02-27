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
	t_list	*lst_env;
	t_list	*parse;
}	t_var;

t_list	*parsing_line(char *str);

#endif

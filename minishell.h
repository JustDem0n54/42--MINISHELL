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
	t_list	*env;
	t_list	*export;
	t_list	*parse;
	char	**data;
	char	*stock_env;
	int		cmd_count;
	int		nbcmd;
	int		entry;
	int 	output;
	char	*cmd;
}	t_var;

// parsing
char	**convert_parse(t_list *lst);
t_list	*parsing_line(char *str);


// init
t_var	*init_struct(t_var *var, char **env);

// builtins 2
void	ft_env(t_var *var, char **tab);
int		ft_cd(char **tab);
char	*ft_pwd(char **tab);
void	ft_echo(t_var *var, char **tab);
void	ft_export(t_var *var, char **tab);

// execve
void	(*ft_cmd(char **cmd))(t_var *var, char **tab);
void	ft_exe(t_var *var, char **tab);
char	**check_command(char **tab, t_var *var);
void	exec_pid(t_var *var, char **tab);
void	execution(t_var *var, char **tab);

// utils2
void	ft_lstadd_next(t_list **lst, t_list *new);
void	print_lst(t_list *lst);

// utils
char	*ft_strncpy(char *str, int size);


// builtins 
char	*ft_pwd(char **tab);
int		ft_cd(char **tab);

#endif

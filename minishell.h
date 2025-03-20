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
# include <signal.h>
# include "libft/libft.h"

typedef struct s_exec
{
	char			**cmd;
	char			*path;
	int				input;
	int				output;
	struct s_exec	*next;
}	t_exec;

typedef	struct s_var
{
	t_list	*env;
	t_list	*export;
	t_list	*parse;
	t_exec	*exec;
	char	**data;
	char	*pwd;
	char	*oldpwd;
	char	*home;
	int		cmd_count;
	int		nbcmd;
	int		status;
}	t_var;

// parsing
char	**convert_parse(t_list *lst);
t_list	*parsing_line(char *str);
void	check_error_parsed(t_list *check);


// init
t_var	*init_struct(t_var *var, char **env);

// builtins 2
void	ft_env(t_var *var, char **tab);
void	ft_export(t_var *var, char **tab);
void	increase_shlvl(t_var *var);

// builtins 3
void	add_var_env(t_var *var, char **tab);
void	ft_unset(t_var *var, char **tab);

// execve
void	(*ft_cmd(char **cmd))(t_var *var, char **tab);
void	ft_exe(t_var *var, char **tab);
char	**check_command(char **tab, t_var *var);
void	exec_pid(t_var *var, char **tab);
char	**do_env(t_list *env);
int		count_command(char **tab);
char	*check_path(char **env, char *cmd);
void	execution(t_var *var, t_exec *exec);

// init_exec
t_exec	*init_exec(t_var *var, char **tab);
void	exec_add_back(t_exec **exec, t_exec *new);
t_exec	*exec_last(t_exec *exec);
t_exec	*ft_execnew(void);

// utils2
void		ft_lstadd_next(t_list **lst, t_list *new);
void		print_lst(t_list *lst);
long int	ft_atol(char *str);
size_t		ft_strlenlongint(long n);
char		*ft_litoa(long int nb);

// utils
char	*ft_strncpy(char *str, int size);


// builtins 
void	ft_echo(t_var *var, char **tab);
void	ft_pwd(t_var *var, char **tab);
void	ft_cd(t_var *var, char **tab);

// unset
size_t	var_name_len(char *tab);

// exit

void	ft_exit(t_var *var, char **tab);
void	ft_free_all(t_var *var);
void	ft_free_exec(t_exec *exec);

int	check_shlv(t_var *var);

// env
void	update_env_pwd_and_old_(t_var *var);


void	ft_ctrl_slash(int sig);
void	ft_ctrl_c(int sig);
#endif


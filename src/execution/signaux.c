#include "../../minishell.h"

// void	(*signal (int sig, void(*ft_signal)(int)))(int);

void	ft_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return;		
}

// void	ft_ctrl_slash(int sig)
// {
// 	if (sig == SIGQUIT)
// 	{
// 		printf("Quitttt(core dumped)\n");
// 		// ft_free_all(var);
// 		exit (0);
// 		return;
// 	}
// 	else
// 		return;		
// }

// int	ft_ctrl_d_heredoc(int sig)
// {
// 	if (line == NULL)
// 	{
// 		ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", 2)
// 		ft_putstr_fd(delimiter);
// 		ft_putstr_fd("')", 2);
// 	}
// }
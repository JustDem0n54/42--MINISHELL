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

void	ft_ctrl_slash(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("Quitttt(core dumped)\n");
		// ft_free_all(var);
		exit (0);
		return;
	}
	else
		return;		
}


	// signal(SIGINT, ft_signal);
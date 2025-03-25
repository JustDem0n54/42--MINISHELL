#include "../../minishell.h"

// void	(*signal (int sig, void(*ft_signal)(int)))(int);

void	ft_ctrl_c_parent(int sig)
{
	// g_ctrl = sig;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return;		
}

void	ft_ctrl_c_child(int sig)
{
	g_ctrl = sig;
	printf("test\n");
	// if (sig == SIGINT)
	// 	rl_replace_line("", 0);
}

void	ft_ctrl_slash(int sig)
{
	// signal(SIGQUIT, SIG_DFL);
	if (sig == SIGQUIT)
		printf("Quit (core dumped)\n");
	g_ctrl = sig;

}

void	manage_signal(int opt)
{
	if (opt == PARENT)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	else if (opt == CHILD)
	{
		signal(SIGQUIT, ft_ctrl_slash);
		signal(SIGINT, ft_ctrl_c_child);
	}
}


// int	ft_ctrl_d_heredoc(int sig)
// {
// 	if (line == NULL)
// 	{
// 		ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", 2)
// 		ft_putstr_fd(delimiter);
// 		ft_putstr_fd("')", 2);
// 	}
// }